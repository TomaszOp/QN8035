#include <Arduino.h>
#include "lib/QN8035.h"

#define SdaPin 9
#define SclPin 8
#define PWMPin 7
#define i2C_ADDRESS 0x10

QN8035 qn8035;


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


    // testing
    /*
    int pwmChannel = 0; // Selects channel 0
    int frequence = 32768; // PWM frequency of 1 KHz
    int resolution = 2; // 8-bit resolution, 256 possible values
    int pwmPin = 7;
    ledcSetup(pwmChannel, frequence, resolution);

    // Assigns the PWM channel to pin 23
    ledcAttachPin(pwmPin, pwmChannel);

    // Create the selected output voltage
    ledcWrite(pwmChannel, 1); // 1.65 V
    */

    //qn8035.StartPWMCrystal(7);

    delay(1000);
    GetChipInfo();

    //pinMode(SdaPin, PULLUP);
    //pinMode(SclPin, PULLUP);


    //qn8035.TunerTest();
    //qn8035.TunerTest2();

    qn8035.TunerInit();

    qn8035.SetVolume(3);

    qn8035.StartPWMCrystal();
}

void loop() {

  delay(30);  

  
  if (Serial.available() > 0)
  {
    char key = Serial.read();

    switch (key)
    {
      case ']':
        qn8035.StopPWMCrystal();
        qn8035.SetFrequencyMHz(qn8035.FrequencyMHz + 0.05);
        qn8035.StartPWMCrystal();
        break;
      case '[':
        qn8035.StopPWMCrystal();
        qn8035.SetFrequencyMHz(qn8035.FrequencyMHz - 0.05);
        qn8035.StartPWMCrystal();
        break;
      
      case '+':
        qn8035.StopPWMCrystal();
        qn8035.SetVolume(qn8035.Volume + 1);
        qn8035.StartPWMCrystal();
        break;

      case '-':
        qn8035.StopPWMCrystal();
        qn8035.SetVolume(qn8035.Volume - 1);
        qn8035.StartPWMCrystal();
        break;

      case '?':
        Serial.println(" > Frequency up");
        Serial.println(" < Frequency down");        
        Serial.println(" + Volume up");
        Serial.println(" - Volume down");
        Serial.println(" i Get frequency");
        break;


      case 'i':
        qn8035.StopPWMCrystal();
        Serial.print("Frequency: ");
        Serial.println(qn8035.GetFrequency());
        qn8035.StartPWMCrystal();
        break;

      case 'r':
        qn8035.StopPWMCrystal();
        GetChipInfo();
        qn8035.StartPWMCrystal();
        break;

      default:
        break;
    }
    
  } 
  


}


