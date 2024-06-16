#include "Arduino.h"

#include "QN8035.h"

QN8035::QN8035()
{
	system1.SetI2C(&i2c);
	cca.SetI2C(&i2c);
	snr.SetI2C(&i2c);
	rssisig.SetI2C(&i2c);
	status1.SetI2C(&i2c);
	cid1.SetI2C(&i2c);
	cid2.SetI2C(&i2c); 
	ch.SetI2C(&i2c);
	ch_start.SetI2C(&i2c);
	ch_stop.SetI2C(&i2c);
	ch_step.SetI2C(&i2c);
	rdsd0.SetI2C(&i2c);
	rdsd1.SetI2C(&i2c);
	rdsd2.SetI2C(&i2c);
	rdsd3.SetI2C(&i2c);
	rdsd4.SetI2C(&i2c);
	rdsd5.SetI2C(&i2c);
	rdsd6.SetI2C(&i2c);
	rdsd7.SetI2C(&i2c);
	rdsstatus2.SetI2C(&i2c);
	vol_ctl.SetI2C(&i2c);
	xtadiv0.SetI2C(&i2c);
	xtadiv1.SetI2C(&i2c);
	xtadiv2.SetI2C(&i2c);
	int_ctrl.SetI2C(&i2c);

	pwmCrystal.AttachPWMPin(DEFAULT_PWMPin);
	
}

QN8035::~QN8035() 
{
}

void QN8035::PrintLog(const char * log)
{
	if(debugSerial)
	Serial.println(log);
}

void QN8035::AttachI2CPins(int _sdaPin, int _sclPin)
{    
	i2c.AttachI2CPins(_sdaPin,_sclPin);      
}
	
void QN8035::SetAddressI2C(byte _address)
{
	i2c.SetAddressI2C(_address);
}

void QN8035::Init()
	{
//SET_REG(REG_SYSTEM1, REG_SYSTEM1_SWRST)
//    #define REG_SYSTEM1     0x00    // Device modes.
//    #define REG_SYSTEM1_SWRST           0x80    // Reset all registers to default values.


//setTunerFrequency(FREQ_TO_WORD(88.0));
//    SET_REG(REG_CH, (tFreq & 0xFF));                // Lo
//    #define REG_CH          0x07
//    SET_REG(REG_CH_STEP, ((tFreq >> 8) & 0x03));    // Hi
//    #define REG_CH_STEP     0x0A
//    usleep(100);
//    SET_REG(REG_SYSTEM1, REG_SYSTEM1_CCA_CH_DIS | REG_SYSTEM1_RXREQ | REG_SYSTEM1_RDSEN);
//    #define REG_SYSTEM1_CCA_CH_DIS      0x01 
//    #define REG_SYSTEM1_RXREQ           0x10
//    #define REG_SYSTEM1_RDSEN           0x08
//    currentFreq = tFreq;
// Sets volume control gain to 0dB.
// SET_REG(REG_VOL_CTL, volume);
//   #define REG_VOL_CTL     0x14 


/*
const unsigned int QN8035[]=
{
0x00,0x80, // initialize ①
0x0a,0x01, // 80.0mHz　②
0x07,0x90, // 
//0x0a,0x01, //82.5 ②
//0x07,0xC2, //
0x00,0b00010001, // receive, seek0　③
0x14,0b00000111, //mute0,de50,vol111　④
0xff,0xff,
};

void setup() {
Wire.begin();
int i=0;
while (QN8035[i] !=0xff) {
Wire.beginTransmission(0x10);  // slave address 0x10
Wire.write(QN8035[i]);      // Register i
Wire.write(QN8035[i+1]);      // data
Wire.endTransmission();     // 

*/
	}

void QN8035::WriteRegister(uint8_t registerNr, uint8_t _data)
{
  Wire.beginTransmission(this->addressI2C);

  Wire.write(registerNr);

  Wire.write(_data);
  Wire.endTransmission();

  delay(I2C_DELAY);
}


uint8_t QN8035::ReadRegister(uint8_t registerNr)
{
  Wire.beginTransmission(this->addressI2C);
  Wire.write(registerNr);
  Wire.endTransmission();

  Wire.requestFrom((int)this->addressI2C, (int)1);
  
  byte data = 0;
  if (Wire.available())
  {
      data = Wire.read();
  }

  delay(I2C_DELAY);
  return data;
}
  

void QN8035::TunerInit()
{
	if(debugSerial){
		Logger.PrintLnLog("TunerInit");
	}

	system1.SetSWRST(1);
	system1.Write();

	delay(100);

	//SetFrequency(INIT_FREQ);
	SetFrequency(FREQ_TO_WORD(92.2));

	SetVolume(REG_VOL_CTL_MAX_ANALOG_GAIN);
}



void QN8035::SetFrequency(uint16_t frequency)
{
	Logger.PrintLog("SetFrequency WORD ");
	Logger.PrintLnLog(frequency);

	FrequencyMHz = WORD_TO_FREQ(frequency);

	uint8_t Lo = (frequency & 0xFF);
	uint8_t Hi = ((frequency >> 8) & 0x03);

	ch.SetCH(Lo);
	ch.Write();
	delay(100);

	ch_step.SetCH(Hi);
	ch_step.Write();

	delay(100);

	system1.SetCCA_CH_DIS(1);
	system1.SetRXREQ(1);
	system1.SetRDSEN(1);

	system1.Write();

	delay(100);
}

void QN8035::SetFrequencyMHz(float frequency)
{
	Logger.PrintLog("SetFrequencyMHz  ");
	Logger.PrintLnLog(frequency);

	if(frequency <= LOW_FREQ)
		frequency = HIGH_FREQ;

	if(frequency >= HIGH_FREQ)
		frequency = LOW_FREQ;

	SetFrequency(FREQ_TO_WORD(frequency));
}


float QN8035::GetFrequency()
{	
	ch.Read();
	uint8_t Lo = ch.GetCH();
	delay(100);

	ch_step.Read();
	uint8_t Hi = ch_step.GetCH();
	
	delay(100);

    Logger.PrintLnLog("GetFrequency");
	Logger.PrintLog("Lo ");
	Logger.PrintLnLog(Lo);
	Logger.PrintLog("Hi ");
	Logger.PrintLnLog(Hi);

	uint16_t value = (Hi << 8) | (Lo & 0xFF);

	this->FrequencyMHz = WORD_TO_FREQ(value);
	
	return this->FrequencyMHz;

	return 0;
}

void QN8035::SetVolume(uint8_t level)
{
	Logger.PrintLog("SetVolume ");
    Logger.PrintLnLog(level);


	vol_ctl.SetMUTE_EN(0);
	vol_ctl.SetTC(0);


	vol_ctl.SetGAIN_DIG(0);

	int8_t value = 7;


	if(level <= REG_VOL_CTL_MIN_ANALOG_GAIN || level == 255)
		level = REG_VOL_CTL_MIN_ANALOG_GAIN;

	if(level >= REG_VOL_CTL_MAX_ANALOG_GAIN)
		level = REG_VOL_CTL_MAX_ANALOG_GAIN;



	if(level == 7)
		value = 0b00000111;
	if(level == 6)
		value = 0b00000110;
	if(level == 5)
		value = 0b00000101;
	if(level == 4)
		value = 0b00000100;
	if(level == 3)
		value = 0b00000011;
	if(level == 2)
		value = 0b00000010;
	if(level == 1)
		value = 0b00000001;
	if(level == 0)
		value = 0b00000000;

	Volume = value;

	vol_ctl.SetGAIN_ANA(Volume);
	vol_ctl.Write();
}

void QN8035::TunerTest()
{
	/*
	0x00,0x80, // initialize ①
	0x0a,0x01, // 80.0mHz　②
	0x07,0x90, // 
	//0x0a,0x01, //82.5 ②
	//0x07,0xC2, //
	0x00,0b00010001, // receive, seek0　③
	0x14,0b00000111, //mute0,de50,vol111　④
	*/

	i2c.WriteRegister(0x00,0x80);
	delay(300);

	i2c.WriteRegister(0x0a,0x01);
	delay(300);
	i2c.WriteRegister(0x07,0x90);
	/*
	i2c.WriteRegister(0x0a,0x01);
	delay(300);
	i2c.WriteRegister(0x07,0xc2);
	*/
	delay(300);
	i2c.WriteRegister(0x00,0b00010001);
	delay(300);
	i2c.WriteRegister(0x14,0b00000111);
	delay(300);
}

void QN8035::TunerTest2()
{
	/*

	// Set channel to 88.0MHz and enable receiving mode.
	setTunerFrequency(FREQ_TO_WORD(88.0));
		SET_REG(REG_CH, (tFreq & 0xFF));                // Lo
		SET_REG(REG_CH_STEP, ((tFreq >> 8) & 0x03));    // Hi
		SET_REG(REG_SYSTEM1, REG_SYSTEM1_CCA_CH_DIS | REG_SYSTEM1_RXREQ | REG_SYSTEM1_RDSEN);
	SET_REG(REG_VOL_CTL, volume);
	*/	


	//delay(I2C_DELAY);
	i2c.WriteRegister(0x00, 0xC0);
	delay(1000);
	i2c.WriteRegister(0x00, 0x80);
	//delay(1000);
	//i2c.WriteRegister(0x00, 0x11);


	delay(1000);


	uint16_t tFreq = FREQ_TO_WORD(92.2);

	delay(I2C_DELAY);
	i2c.WriteRegister(0x07, (tFreq & 0xFF));
	delay(I2C_DELAY);
	i2c.WriteRegister(0x0a, ((tFreq >> 8) & 0x03));
	delay(I2C_DELAY);


	uint16_t vREG_SYSTEM1_CCA_CH_DIS     = 0x01;
	uint16_t vREG_SYSTEM1_RXREQ = 0x10;
	uint16_t vREG_SYSTEM1_RDSEN = 0x08; 

	i2c.WriteRegister(0x00, vREG_SYSTEM1_CCA_CH_DIS | vREG_SYSTEM1_RXREQ| vREG_SYSTEM1_RDSEN);
	//i2c.WriteRegister(0x00, vREG_SYSTEM1_CCA_CH_DIS | vREG_SYSTEM1_RXREQ);
	delay(I2C_DELAY);
    delay(1000);

	i2c.WriteRegister(0x14, 0x07 );
	delay(I2C_DELAY);
}

void QN8035::StartPWMCrystal(int _Pin)
{
	this->pwmCrystal.AttachPWMPin(_Pin);
	this->pwmCrystal.Start();
}

void QN8035::StopPWMCrystal()
{
	this->pwmCrystal.Stop();
}