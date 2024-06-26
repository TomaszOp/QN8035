#include <Arduino.h>
#include "lib/QN8035.h"

#define SdaPin 9
#define SclPin 8
// add resistor 10k PWMPin and XCLK
#define PWMPin 7
#define i2C_ADDRESS 0x10

QN8035 qn8035;

void scanI2C() {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
  delay(5000);          
}


void GetChipInfo()
{
  qn8035.cid1.Read();

  Serial.print("Chip ID for product family: ");
  Serial.println(qn8035.cid1.GetCID1());

  Serial.print("Chip ID for minor revision: ");
  Serial.println(qn8035.cid1.GetCID2());


  qn8035.cid2.Read();

  Serial.print("Chip ID for product ID: ");
  Serial.println(qn8035.cid2.GetCID3());

  Serial.print("Chip ID for major revision: ");
  Serial.println(qn8035.cid2.GetCID4());

  delay(300);
}


void setup() 
{
    Serial.begin(115200);
    while (!Serial);

    /*
    configure pins
    */
    qn8035.AttachI2CPins(SdaPin, SclPin);
    qn8035.AttachPWMPin(PWMPin);

    /*
    address i2c
    */
    qn8035.SetAddressI2C(i2C_ADDRESS);

    /*
    on debug message on uart
    */
    qn8035.i2c.debugSerial = true;
    qn8035.debug = true;

    // testing
    /*
    int pwmChannel = 0; // Selects channel 0
    int frequence = 32768; // PWM frequency of  KHz
    int resolution = 2; // bit resolution, possible values
    int pwmPin = 7;
    ledcSetup(pwmChannel, frequence, resolution);

    // Assigns the PWM channel to pin 
    ledcAttachPin(pwmPin, pwmChannel);

    // Create the selected output 
    ledcWrite(pwmChannel, 1); 
    */

    //qn8035.StartPWMCrystal(7);

    delay(1000);
    GetChipInfo();

    //pinMode(SdaPin, PULLUP);
    //pinMode(SclPin, PULLUP);

    qn8035.TunerInit();

    qn8035.SetVolume(3);

    qn8035.StartPWMCrystal();
}

void loop() 
{
  float freqNext = 0;

  delay(30);  

  if (Serial.available() > 0)
  {
    char key = Serial.read();

    switch (key)
    {
      case ']':
        qn8035.SetFrequencyMHz(qn8035.FrequencyMHz + 0.05);
        break;
      case '[':
        qn8035.SetFrequencyMHz(qn8035.FrequencyMHz - 0.05);
        break;
      
      case '+':
        qn8035.SetVolume(qn8035.Volume + 1);
        Serial.print("Volume: ");
        Serial.println(qn8035.Volume);
        break;

      case '-':
        qn8035.SetVolume(qn8035.Volume - 1);
        Serial.print("Volume: ");
        Serial.println(qn8035.Volume);
        break;

      case '?':
        Serial.println(" > Frequency up");
        Serial.println(" < Frequency down");        
        Serial.println(" + Volume up");
        Serial.println(" - Volume down");
        Serial.println(" i Get frequency");
        Serial.println(" r Chip info");
        Serial.println(" m Set mute");
        Serial.println(" s Scan i2c");
        break;


      case 'i':
        Serial.print("Frequency: ");
        Serial.println(qn8035.GetFrequencyMHz());
        break;

      case 'r':
        GetChipInfo();
        break;

      case 'm':
        qn8035.SetMute((qn8035.Mute ? false : true));
        Serial.print("Mute: ");
        Serial.println(qn8035.Mute ? 1 : 0);
        break;


      case 's':
        scanI2C();
        break;

      case 'I':
        Serial.print("RSSI: ");
        Serial.println(qn8035.GetRssi());
        Serial.print("SNR: ");
        Serial.println(qn8035.GetSnr());
        break;

      case '>':
        freqNext = qn8035.ScanFrequencyUp();
        Serial.print("Frequency: ");
        Serial.println(freqNext);
        break;

      case '<':
        freqNext = qn8035.ScanFrequencyDown();
        Serial.print("Frequency: ");
        Serial.println(freqNext);
        break;

      case 't':
        qn8035.TunerTest();
        break;


      default:
        break;
    }
  } 
}

