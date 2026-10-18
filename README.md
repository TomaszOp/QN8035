Library for QN8035 (radio FM chip)

Tested on esp32C3<br>
Compile platformio (framework = arduino)<br>
chip radio - serial number 8035 0259 4TCE <br>
<br>
not everything is finished<br>
work:<br>
 Initialize chip<br>
 SetFrequency<br>
 GetFrequency<br>
 SetVolumeA<br>
 SetMute<br>
 SetMono<br>
 SetTestTone (1 kHz)<br>
 GetSnr<br>
 GetRssi<br>
 ScanFrequency (to improve parameter XCCADL now is 4)<br>
 <br>
 to do:<br>
 read RDS
 <br>
 <br>
All registers (and setting fields) are finished <br>
I didn't have a quartz, i made a virtual quartz using PWM (add resistor 10k to PWMPin and XCLK)


## Test tone 1 kHz

The chip can replace the received audio with an internal 1 kHz tone (`S1K_EN`, Reg 18h bit 4). Useful to test the audio path (amplifier, headphones, wiring) without a station.

```cpp
qn8035.SetTestTone(true);   // 1 kHz on the audio output
qn8035.SetTestTone(false);  // back to radio
```

Works in RX mode (after `TunerInit()`, not in standby). Volume (`SetVolume`) and `SetMute` still apply. `TunerInit()` turns the tone off (soft reset). Serial console in `main.cpp`: `T` tone on/off.

## RDS

Enable RDS after `TunerInit()` and tuning to a station. RDS stays enabled when the frequency changes or a scan runs; data of the previous station is cleared.

```cpp
qn8035.TunerInit();
qn8035.SetFrequencyMHz(96.0);
qn8035.InitRDS();          // same as SetRDS(true), SetRDS(false) disables RDS
```

Call `ReadRDS()` often in `loop()` (every < 80 ms, the chip receives a new group about every 88 ms), avoid long `delay()`. It returns `true` when a new valid group was decoded.

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

Public fields:

| Field | Description |
|---|---|
| `RdsSync` | `true` when the chip is synchronized to an RDS signal |
| `RdsPI` | Program Identification, 16 bit (print as HEX) |
| `RdsPTY` | Program Type, 0-31 |
| `RdsPS` | Program Service name, 8 chars + `\0` |
| `RdsRT` | RadioText, up to 64 chars + `\0` |

Decoded groups: 0A/0B (PS) and 2A/2B (RadioText). Blocks with errors are skipped. PS and RT are built piece by piece (PS 2 chars, RT 4 chars per group), missing parts are spaces. `ClearRDS()` clears the data.

Serial console in `main.cpp` (115200): `d` RDS on/off, `D` print RDS info. With RDS on, changes of PS and RT are printed automatically. Set `qn8035.i2c.debugSerial = false;` first, otherwise I2C logs flood the console.

RDS needs a stronger signal than audio. If `RdsSync` stays 0, check RSSI/SNR (`I`) and the antenna.

Not yet tested on hardware: byte order of RDSD0..RDSD7 is assumed MSB first (RDSD0 = high byte of block A). Polish stations have PI starting with 3; if PI looks byte swapped, swap the bytes in `ReadRDS()`.
