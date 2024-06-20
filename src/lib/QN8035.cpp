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

void QN8035::AttachI2CPins(int _sdaPin, int _sclPin)
{    
	i2c.AttachI2CPins(_sdaPin,_sclPin);      
}
	
void QN8035::AttachPWMPin(int _pwmPin)
{
	pwmCrystal.AttachPWMPin(_pwmPin);
}

void QN8035::SetAddressI2C(byte _address)
{
	i2c.SetAddressI2C(_address);
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
  
void QN8035::SetWaveClockType(CCA__XTAL_INJ value)
{
	cca.SetXTAL_INJ(SquareWaveClock);
}

void QN8035::TunerInit()
{
	if(debug)
	{
		Logger.PrintLnLog("TunerInit");
	}

	system1.SetSWRST(1);
	system1.SetRECAL(1);
	system1.Write();

	delay(1000);

	//SetFrequency(INIT_FREQ);
	SetFrequency(FREQ_TO_WORD(92.2));

	SetVolume(REG_VOL_CTL_START_ANALOG_GAIN);
	delay(I2C_DELAY);


	// clock wave digital clock -- Square
	cca.SetXTAL_INJ(SquareWaveClock);


// testing others crytal 

//crystal clock is 32768HZ
//#define QND_XTAL_DIV0                   0x01
//#define QND_XTAL_DIV1                   0x08
//#define QND_XTAL_DIV2                   0x5C

//crystal clock is 12MHZ
//#define QND_XTAL_DIV0                  0x6e
//#define QND_XTAL_DIV1                  0x01
//#define QND_XTAL_DIV2                  0x54

//crystal clock is 4MHZ
//#define QND_XTAL_DIV0                  0x7a
//#define QND_XTAL_DIV1                  0x00
//#define QND_XTAL_DIV2                  0x54

//	this->i2c.WriteRegister(XTAL_DIV0, QND_XTAL_DIV0);
//	this->i2c.WriteRegister(XTAL_DIV1, QND_XTAL_DIV1);
//	this->i2c.WriteRegister(XTAL_DIV2, QND_XTAL_DIV2);

}



void QN8035::SetFrequency(uint16_t frequency)
{
	if(debug)
	{
		Logger.PrintLog("SetFrequency WORD ");
		Logger.PrintLnLog(frequency);
	}

	FrequencyMHz = WORD_TO_FREQ(frequency);
	FrequencyCurrent = frequency;

	uint8_t Lo = (frequency & 0xFF);
	uint8_t Hi = ((frequency >> 8) & 0x03);

	ch.SetCH(Lo);
	ch.Write();
	delay(100);

	ch_step.SetCH(Hi);
	ch_step.SetFSTEP(0);
	ch_step.SetCH_STP(0);
	ch_step.SetCH_STA(0);

	ch_step.Write();

	delay(100);

	system1.SetCCA_CH_DIS(1);
	system1.SetRXREQ(1);
	system1.SetRDSEN(0);
	system1.SetSWRST(0);	
	system1.SetRECAL(0);

	system1.Write();

	delay(100);
}

void QN8035::SetFrequencyMHz(float frequency)
{
	if(debug)
	{
		Logger.PrintLog("SetFrequencyMHz  ");
		Logger.PrintLnLog(frequency);
	}

	if(frequency <= LOW_FREQ)
		frequency = HIGH_FREQ;

	if(frequency >= HIGH_FREQ)
		frequency = LOW_FREQ;

	SetFrequency(FREQ_TO_WORD(frequency));
}


float QN8035::GetFrequencyMHz()
{	
	ch.Read();
	uint8_t Lo = ch.GetCH();
	delay(100);

	ch_step.Read();
	uint8_t Hi = ch_step.GetCH();
	
	delay(100);

	if(debug)
	{
		Logger.PrintLnLog("GetFrequency");
		Logger.PrintLog("Lo ");
		Logger.PrintLnLog(Lo);
		Logger.PrintLog("Hi ");
		Logger.PrintLnLog(Hi);
	}

	uint16_t value = (Hi << 8) | (Lo & 0xFF);

	this->FrequencyMHz = WORD_TO_FREQ(value);
	
	return this->FrequencyMHz;

	return 0;
}

float QN8035::ScanFrequencyUp()
{
	if(debug)
	{
		Logger.PrintLnLog("ScanFrequencyUp");
	}

	return Scan(FrequencyMHz, HIGH_FREQ);
}

float QN8035::ScanFrequencyDown()
{
	if(debug)
	{
		Logger.PrintLnLog("ScanFrequencyDown");
	}

	return Scan(LOW_FREQ, FrequencyMHz);
}

float QN8035::Scan(float freqStartMhz, float freqEndMhz)
{
	uint16_t freqStart = FREQ_TO_WORD(freqStartMhz);
	uint16_t freqEnd = FREQ_TO_WORD(freqEndMhz);

	if(freqStart < freqEndMhz)
	{
		freqStart = freqStart + 4;
	}
	else if (freqStart > freqEndMhz)
	{
		freqEnd = freqEnd - 4;
	}


	uint8_t hiFreqStart = (freqStart >> 8) & 0b00000011;
	uint8_t loFreqStart = (freqStart & 0xFF);

	uint8_t hiFreqEnd = (freqEnd >> 8) & 0b00000011;
	uint8_t loFreqEnd = (freqEnd & 0xFF);

	ch_start.SetCH_STA(loFreqStart);
	ch_step.SetCH_STA(hiFreqStart);

	ch_stop.SetCH_STP(loFreqEnd);
	ch_step.SetCH_STP(hiFreqEnd);

	ch.SetCH(loFreqStart);
	ch_step.SetCH(hiFreqStart);

	uint8_t REG_CH_STEP_50KHZ  = 0x00;
	uint8_t REG_CH_STEP_100KHZ = 0x40;
	uint8_t REG_CH_STEP_200KHZ = 0x80;
	uint8_t REG_CH_STEP =    0x0A;
	ch_step.SetFSTEP(REG_CH_STEP_50KHZ);


	ch_start.Write();
	ch_stop.Write();
	ch_step.Write();

	uint8_t CCA_LEVEL =  0x04;
	cca.SetXCCADL(CCA_LEVEL);

	system1.SetCCA_CH_DIS(0);
	system1.SetCHSC(1);
	system1.SetRXREQ(1);
	system1.SetSTNBY(0);

	system1.Write();

    return CheckScanComplete();
	
}

float QN8035::CheckScanComplete()
{
	uint8_t timeout, isFound, freqFix;
    float newFreqMhz;
    
    timeout = 25;
    isFound = 0;
	newFreqMhz = 0;

	if(debug)
	{
		Logger.PrintLnLog("CheckScanComplete");
	}

    do
    {
		if(debug)
		{
			Logger.PrintLog("read ");
			Logger.PrintLnLog(timeout);
		}

        // Check for end of auto scan operation.
		uint8_t valuesystem1 = system1.Read();
		
		#define REG_SYSTEM1_CHSC 0x02

        if((valuesystem1 & REG_SYSTEM1_CHSC) == 0)
        {
            isFound = 1;

			if(debug)
			{
				Logger.PrintLnLog("Found");
			}

			ch.Read();
			ch_step.Read();
			u_int8_t lo = ch.GetCH();
			u_int8_t hi = ch_step.GetCH();

			u_int16_t newFreq = (lo) | ((hi & 0x03) << 8); 
			newFreqMhz = WORD_TO_FREQ(newFreq);

			if(debug)
			{
				Logger.PrintLnLog("Found");

				Logger.PrintLog("Found newFreqMhz " );
				Logger.PrintLnLog(newFreqMhz);
			}

            break;
        }
            
        timeout--;
        usleep(5000);        
    } 
    while (timeout != 0);

	return newFreqMhz;
}

void QN8035::SetVolume(uint8_t level)
{
	if(debug)
	{
		Logger.PrintLog("SetVolume ");
		Logger.PrintLnLog(level);
	}

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

uint16_t QN8035::SetVolume(VolumeDirection direction)
{
	if(direction == VOLUME_DOWN)
	{
		SetVolume(this->Volume - 1);
	}
	else if(direction == VOLUME_UP)
	{
		SetVolume(this->Volume + 1);
	}

	return this->Volume;
}


void QN8035::SetMute(bool value)
{
	if(debug)
	{
		Logger.PrintLog("Mute ");
		Logger.PrintLnLog((value ? (uint8_t)1 : (uint8_t)0));
	}

	this->Mute = value;

	vol_ctl.SetMUTE_EN((value ? (uint8_t)1 : (uint8_t)0));
	vol_ctl.Write();
}


void QN8035::TunerTest()
{
	float freqStartMhz = 90;
	float freqEndMhz = 108;


	uint16_t freqStart = FREQ_TO_WORD(freqStartMhz);
	uint16_t freqEnd = FREQ_TO_WORD(freqEndMhz);

	uint8_t hiFreqStart = (freqStart >> 8) & 0b00000011;
	uint8_t loFreqStart = (freqStart & 0xFF);

	uint8_t hiFreqEnd = (freqEnd >> 8) & 0b00000011;
	uint8_t loFreqEnd = (freqEnd & 0xFF);

	ch_start.SetCH_STA(loFreqStart);
	ch_step.SetCH_STA(hiFreqStart);

	ch_stop.SetCH_STP(loFreqEnd);
	ch_step.SetCH_STP(hiFreqEnd);

	ch.SetCH(loFreqStart);
	ch_step.SetCH(hiFreqStart);

	uint8_t REG_CH_STEP_50KHZ  = 0x00;
	uint8_t REG_CH_STEP_100KHZ = 0x40;
	uint8_t REG_CH_STEP_200KHZ = 0x80;
	uint8_t REG_CH_STEP =    0x0A;
	ch_step.SetFSTEP(REG_CH_STEP_50KHZ);


	ch_start.Write();
	ch_stop.Write();
	ch_step.Write();

	uint8_t CCA_LEVEL =  0x04;
	cca.SetXCCADL(CCA_LEVEL);


	system1.SetCCA_CH_DIS(0);
	system1.SetCHSC(1);
	system1.SetRXREQ(1);
	system1.SetSTNBY(0);

	system1.Write();

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
	FrequencyCurrent = tFreq;

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

void QN8035::StartPWMCrystal()
{
	this->pwmCrystal.Start();
}

void QN8035::StopPWMCrystal()
{
	this->pwmCrystal.Stop();
}

int8_t QN8035::GetSnr()
{
	snr.Read();

	return snr.GetSNRDB();
}

int8_t QN8035::GetRssi()
{
	rssisig.Read();

	return rssisig.GetRSSIDB();
}