# QN8035

Arduino library for the **QN8035** FM radio receiver chip (Quintic), 60–108 MHz, I2C control, RDS/RBDS.

- Tested on ESP32-C3 (PlatformIO, `framework = arduino`, builds with arduino-esp32 core 3.3.9)
- Chip used for testing: marking `8035 0259 4TCE`
- Datasheet: [doc/QN8035.pdf](doc/QN8035.pdf) (Rev 0.08), links in [doc/README.md](doc/README.md)
- All registers (00h–18h) and their bit fields are implemented as classes in `src/lib/Registers`

The code currently uses ESP32-specific APIs (`Wire.begin(sda, scl)`, LEDC PWM), so it does not build for other boards yet.

## Hardware

| QN8035 | ESP32-C3 (example in `main.cpp`) |
|---|---|
| SDA | GPIO 9 |
| SCL | GPIO 8 |
| XCLK | GPIO 7 via 10 kΩ resistor (virtual crystal, see below) |

I2C address: `0x10`.

### Virtual crystal

The chip needs a 32.768 kHz reference clock. Without a real crystal, the library can generate it with PWM (`PWM_CRYSTAL`). Connect the PWM pin to XCLK through a 10 kΩ resistor and start the clock **before** `TunerInit()`. The chip needs it for reset and calibration.

The LEDC API is selected automatically from `ESP_ARDUINO_VERSION_MAJOR` (`ledcAttach` on core 3.x, `ledcSetup`/`ledcAttachPin` on older cores).

## Quick start

```cpp
#include <Arduino.h>
#include "lib/QN8035.h"

QN8035 qn8035;

void setup()
{
  Serial.begin(115200);

  qn8035.AttachI2CPins(9, 8);   // SDA, SCL
  qn8035.AttachPWMPin(7);       // virtual crystal
  qn8035.SetAddressI2C(0x10);

  qn8035.StartPWMCrystal();     // clock before init
  delay(1000);

  qn8035.TunerInit();
  qn8035.SetFrequencyMHz(96.0);
  qn8035.SetVolume(40);         // 0 - 47
}

void loop()
{
}
```

## API

### Init and power

| Function | Description |
|---|---|
| `AttachI2CPins(sda, scl)` | Starts `Wire` on the given pins, 400 kHz |
| `SetAddressI2C(addr)` | I2C address (default `0x10`) |
| `AttachPWMPin(pin)` | Pin for the virtual crystal |
| `StartPWMCrystal()` / `StopPWMCrystal()` | 32.768 kHz PWM clock on/off |
| `TunerInit()` | Soft reset, recalibration, digital clock input, tunes to 92.2 MHz (takes about 1 s) |
| `SetWaveClockType(SquareWaveClock / SineWaveClock)` | Reference clock type (`XTAL_INJ`) |
| `SetStandby(bool)` | `true` = standby, `false` = back to RX mode |

### Tuning

| Function | Description |
|---|---|
| `SetFrequencyMHz(float)` | Tune, 88.0–108.0 MHz, 50 kHz resolution |
| `SetFrequency(uint16_t)` | Tune by channel index, `FREQ_TO_WORD(mhz)` |
| `GetFrequencyMHz()` | Read the current frequency from the chip |
| `ScanFrequencyUp()` / `ScanFrequencyDown()` | Seek the next station (chip CCA), returns MHz or `0` if nothing was found |
| `SetScanStep(FSTEP__50kHz / FSTEP__100kHz / FSTEP__200kHz)` | Seek step |
| `SetCCALevel(0-63)` | Seek threshold: channel is valid if RSSI (dBµV) > level − 10. Default `4` |
| `GetRssi()` | Signal level in dBµV |
| `GetSnr()` | Signal-to-noise ratio in dB |

Fields: `FrequencyMHz`, `FrequencyCurrent` (channel index), `ScanStep`, `CCALevel`.

### Audio

| Function | Description |
|---|---|
| `SetVolume(0-47)` | Volume in 1 dB steps: 47 = 0 dB, 0 = −47 dB (analog 6 dB + digital 1 dB steps) |
| `SetVolume(VOLUME_UP / VOLUME_DOWN)` | Step by 1 dB, returns the new level |
| `GetVolume()` | Reads the volume from the chip (0–47) |
| `SetVolumeA(0-7)` | Analog gain only, 6 dB steps (7 = 0 dB, 0 = −42 dB) |
| `SetMute(bool)` | Mute audio output |
| `SetMono(bool)` | `true` forces mono, `false` = automatic stereo/mono |
| `IsStereo()` | `true` when the station is received in stereo |
| `SetTestTone(bool)` | Internal 1 kHz test tone, see below |

Fields: `VolumeFull` (0–47), `Volume` (analog 0–7), `Mute`, `Mono`, `TestTone`.

De-emphasis is set to 50 µs (Europe).

### Test tone 1 kHz

The chip can replace the received audio with an internal 1 kHz tone (`S1K_EN`, Reg 18h bit 4). Use it to test the audio path (amplifier, headphones, wiring) without a station.

```cpp
qn8035.SetTestTone(true);   // 1 kHz on the audio output
qn8035.SetTestTone(false);  // back to radio
```

Works in RX mode only (after `TunerInit()`, not in standby). Volume and mute still apply. `TunerInit()` turns the tone off (soft reset).

### RDS

Enable RDS after `TunerInit()` and tuning to a station. RDS stays enabled when the frequency changes or a scan runs. Data of the previous station is cleared.

```cpp
qn8035.TunerInit();
qn8035.SetFrequencyMHz(96.0);
qn8035.InitRDS();          // same as SetRDS(true), SetRDS(false) disables RDS
```

Call `ReadRDS()` often in `loop()` and avoid long `delay()`, because the chip receives a new group about every 88 ms. It returns `true` when a new valid group was decoded.

```cpp
void loop()
{
  if (qn8035.ReadRDS())
  {
    Serial.println(qn8035.RdsPS);   // station name
    Serial.println(qn8035.RdsRT);   // RadioText
  }
}
```

| Field | Description |
|---|---|
| `RdsEnabled` | RDS on/off |
| `RdsSync` | `true` when the chip is synchronized to an RDS signal |
| `RdsPI` | Program Identification, 16 bit (print as HEX) |
| `RdsPTY` | Program Type, 0–31 |
| `RdsPS` | Program Service name, 8 chars + `\0` |
| `RdsRT` | RadioText, up to 64 chars + `\0` |

Decoded groups are 0A/0B (PS) and 2A/2B (RadioText), and blocks with errors are skipped. PS and RT are built piece by piece (PS 2 chars per group, RT 4 chars per group in 2A and 2 chars in 2B), and missing parts are spaces. `ClearRDS()` clears the data.

RDS needs a stronger signal than audio. If `RdsSync` stays 0, check RSSI/SNR and the antenna.

### Debug

- `qn8035.debug = true;` logs library calls to `Serial`
- `qn8035.i2c.debugSerial = true;` logs every I2C read/write (very verbose; turn it off when using RDS)

## Serial console (`src/main.cpp`)

The example sketch accepts single-key commands at 115200 baud:

| Key | Action |
|---|---|
| `]` / `[` | Frequency +/− 50 kHz |
| `>` / `<` | Seek next station up / down |
| `+` / `-` | Analog volume up / down |
| `i` | Print frequency |
| `I` | Print RSSI and SNR |
| `m` | Mute on/off |
| `T` | 1 kHz test tone on/off |
| `d` | RDS on/off |
| `D` | Print RDS info (sync, PI, PTY, PS, RT) |
| `r` | Chip ID info |
| `s` | I2C bus scan |
| `?` | Help |

With RDS on, changes of PS and RT are printed automatically.

## Status

Working (tested on hardware): init, tuning, volume, mute, mono, RSSI/SNR, seek.

Implemented but not yet tested on hardware:
- RDS. The byte order of RDSD0..RDSD7 is assumed MSB first (RDSD0 = high byte of block A). Polish stations have a PI starting with `3`; if PI looks byte-swapped, swap the bytes in `ReadRDS()`.
- 1 kHz test tone.
- PWM clock on arduino-esp32 core 2.x.

Known limitations / to do:
- `ReadRDS()` is slow because of fixed I2C delays, so some RDS groups may be missed
- When seek finds no station, the chip stays at the end of the band
- Band fixed to 88–108 MHz; de-emphasis fixed to 50 µs
- Only the 32.768 kHz reference clock is configured (`XTAL_DIV` registers at defaults)
- No RDS clock time (CT), AF, TP/TA yet
- No interrupt pin support (RDS / CCA interrupt)
- ESP32 only
