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

	Mute = false;
	Mono = false;
	ScanStep = FSTEP__50kHz;
	CCALevel = DEFAULT_CCA_LEVEL;

	RdsEnabled = false;
	ClearRDS();
	
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
	cca.SetXTAL_INJ(value);
	cca.Write();
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

	// release reset, keep RECAL until SetFrequency
	system1.SetSWRST(0);
	system1.Write();

	// clock wave digital clock -- Square
	cca.SetXTAL_INJ(SquareWaveClock);
	cca.Write();

	//SetFrequency(INIT_FREQ);
	SetFrequency(FREQ_TO_WORD(92.2));

	SetVolumeA(REG_VOL_CTL_START_ANALOG_GAIN);
	delay(I2C_DELAY);



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

void QN8035::SetStandby(bool value)
{
	if(debug)
	{
		Logger.PrintLog("SetStandby ");
		Logger.PrintLnLog((value ? (uint8_t)1 : (uint8_t)0));
	}

	// RXREQ overwrites STNBY, so standby needs RXREQ = 0, wake up needs RXREQ = 1
	system1.SetCHSC(0);
	system1.SetSTNBY((value ? 1: 0));
	system1.SetRXREQ((value ? 0: 1));
	system1.Write();
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

	ClearRDS();

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
	system1.SetCHSC(0);
	system1.SetSTNBY(0);
	system1.SetRXREQ(1);
	system1.SetRDSEN((RdsEnabled ? 1 : 0));
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

	else if(frequency >= HIGH_FREQ)
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

	return Scan(FrequencyMHz + 0.2, HIGH_FREQ);
}

float QN8035::ScanFrequencyDown()
{
	if(debug)
	{
		Logger.PrintLnLog("ScanFrequencyDown");
	}

	return Scan(FrequencyMHz - 0.2, LOW_FREQ);
}

void QN8035::SetScanStep(CH_STEP__FSTEP step)
{
	if(debug)
	{
		Logger.PrintLog("SetScanStep ");
		Logger.PrintLnLog((uint8_t)step);
	}

	ScanStep = step;
}

CH_STEP__FSTEP QN8035::GetScanStep()
{
	return ScanStep;
}

void QN8035::SetCCALevel(uint8_t level)
{
	if(level > MAX_CCA_LEVEL)
		level = MAX_CCA_LEVEL;

	if(debug)
	{
		Logger.PrintLog("SetCCALevel ");
		Logger.PrintLnLog(level);
	}

	CCALevel = level;
}

uint8_t QN8035::GetCCALevel()
{
	return CCALevel;
}

float QN8035::Scan(float freqStartMhz, float freqEndMhz)
{
	uint16_t freqStart = FREQ_TO_WORD(freqStartMhz);
	uint16_t freqEnd = FREQ_TO_WORD(freqEndMhz);

	ClearRDS();

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

	ch_step.SetFSTEP(ScanStep);


	ch_start.Write();
	ch_stop.Write();
	ch_step.Write();

	cca.SetXCCADL(CCALevel);
	cca.Write();

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
    
    timeout = 170;
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

			status1.Read();
			if(status1.GetRXCCA_FAIL() == RXCCA_FAIL__failstofind)
			{
				if(debug)
				{
					Logger.PrintLnLog("Not found (RXCCA_FAIL)");
				}
				break;
			}

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

			FrequencyCurrent = newFreq;
			FrequencyMHz = newFreqMhz;

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

void QN8035::SetVolumeA(uint8_t level)
{
	if(debug)
	{
		Logger.PrintLog("SetVolumeA ");
		Logger.PrintLnLog(level);
	}

	vol_ctl.SetMUTE_EN((Mute ? 1 : 0));
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
	VolumeFull = 5 + Volume * 6;

	vol_ctl.SetGAIN_ANA(Volume);
	vol_ctl.Write();
}

uint8_t QN8035::GetVolumeA()
{
	vol_ctl.Read();

	Volume = vol_ctl.GetGAIN_ANA();

	if(debug)
	{
		Logger.PrintLog("GetVolumeA ");
		Logger.PrintLnLog(Volume);
	}

	return Volume;
}

uint8_t QN8035::SetVolumeA(VolumeDirection direction)
{
	if(direction == VOLUME_DOWN)
	{
		SetVolumeA(this->Volume - 1);
	}
	else if(direction == VOLUME_UP)
	{
		SetVolumeA(this->Volume + 1);
	}

	return this->Volume;
}

void QN8035::SetVolume(uint8_t level)
{
	// level - 1 from 0 gives 255
	if(level == 255)
		level = VOLUME_MIN;

	if(level > VOLUME_MAX)
		level = VOLUME_MAX;

	if(debug)
	{
		Logger.PrintLog("SetVolume ");
		Logger.PrintLnLog(level);
	}

	// attenuation in dB, split into analog 6 dB steps and digital 1 dB steps
	uint8_t attenuation = VOLUME_MAX - level;
	uint8_t analog = 7 - (attenuation / 6);
	uint8_t digital = attenuation % 6;

	VolumeFull = level;
	Volume = analog;

	vol_ctl.SetMUTE_EN((Mute ? 1 : 0));
	vol_ctl.SetTC(0);
	vol_ctl.SetGAIN_DIG(digital);
	vol_ctl.SetGAIN_ANA(analog);
	vol_ctl.Write();
}

uint8_t QN8035::SetVolume(VolumeDirection direction)
{
	if(direction == VOLUME_DOWN)
	{
		SetVolume((uint8_t)(this->VolumeFull - 1));
	}
	else if(direction == VOLUME_UP)
	{
		SetVolume((uint8_t)(this->VolumeFull + 1));
	}

	return this->VolumeFull;
}

uint8_t QN8035::GetVolume()
{
	vol_ctl.Read();

	uint8_t analog = vol_ctl.GetGAIN_ANA();
	uint8_t digital = vol_ctl.GetGAIN_DIG();

	// 110 and 111 are not defined in datasheet
	if(digital > 5)
		digital = 5;

	Volume = analog;
	VolumeFull = VOLUME_MAX - ((7 - analog) * 6 + digital);

	if(debug)
	{
		Logger.PrintLog("GetVolume ");
		Logger.PrintLnLog(VolumeFull);
	}

	return VolumeFull;
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


void QN8035::SetMono(bool value)
{
	if(debug)
	{
		Logger.PrintLog("Mono ");
		Logger.PrintLnLog((value ? (uint8_t)1 : (uint8_t)0));
	}

	this->Mono = value;

	system1.SetFORCE_MO((value ? 1 : 0));
	system1.Write();
}

bool QN8035::GetMono()
{
	return this->Mono;
}

bool QN8035::IsStereo()
{
	status1.Read();

	return status1.GetST_MO_RX() == ST_MO_RX__Stereo;
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

void QN8035::InitRDS()
{
	SetRDS(true);
}

void QN8035::SetRDS(bool value)
{
	if(debug)
	{
		Logger.PrintLog("SetRDS ");
		Logger.PrintLnLog((value ? (uint8_t)1 : (uint8_t)0));
	}

	RdsEnabled = value;
	ClearRDS();

	system1.SetRDSEN((value ? 1 : 0));
	system1.Write();
}

void QN8035::ClearRDS()
{
	RdsSync = false;
	RdsPI = 0;
	RdsPTY = 0;

	memset(RdsPS, ' ', 8);
	RdsPS[8] = '\0';

	memset(RdsRT, ' ', 64);
	RdsRT[64] = '\0';

	rdsLastUpdate = 0xFF;
	rdsTextAB = 0xFF;
}

/*
datasheet 5.13 RDS:
e. RDSSYNC (Reg13h[4]) = 1 -> RDS signal received
f. RDS_RXTXUPD (Reg13h[7]) toggled -> new group (8 bytes) in RDSD0..RDSD7
g. Reg13h[3:0] = 0 -> blocks valid
h. read RDSD0..RDSD7
*/
bool QN8035::ReadRDS()
{
	if(!RdsEnabled)
		return false;

	rdsstatus2.Read();

	RdsSync = rdsstatus2.GetRDSSYNC();
	if(!RdsSync)
		return false;

	uint8_t update = rdsstatus2.GetRDS_RXTXUPD();
	if(update == rdsLastUpdate)
		return false;

	rdsLastUpdate = update;

	uint8_t errors = rdsstatus2.Data & 0b00001111;

	// block B (group type) is needed to decode anything
	if(rdsstatus2.GetRDS1ERR())
		return false;

	uint16_t blockA = ((uint16_t)rdsd0.Read() << 8) | rdsd1.Read();
	uint16_t blockB = ((uint16_t)rdsd2.Read() << 8) | rdsd3.Read();
	uint16_t blockC = ((uint16_t)rdsd4.Read() << 8) | rdsd5.Read();
	uint16_t blockD = ((uint16_t)rdsd6.Read() << 8) | rdsd7.Read();

	// new group arrived during reading -> data mixed, skip
	rdsstatus2.Read();
	if(rdsstatus2.GetRDS_RXTXUPD() != rdsLastUpdate)
	{
		rdsLastUpdate = rdsstatus2.GetRDS_RXTXUPD();
		return false;
	}

	DecodeRDS(blockA, blockB, blockC, blockD, errors);

	return true;
}

void QN8035::DecodeRDS(uint16_t blockA, uint16_t blockB, uint16_t blockC, uint16_t blockD, uint8_t errors)
{
	bool okA = (errors & 0b00001000) == 0;
	bool okC = (errors & 0b00000010) == 0;
	bool okD = (errors & 0b00000001) == 0;

	uint8_t groupType = (blockB >> 12) & 0x0F;
	uint8_t versionB = (blockB >> 11) & 0x01;

	if(okA)
		RdsPI = blockA;

	RdsPTY = (blockB >> 5) & 0x1F;

	if(debug)
	{
		Logger.PrintLog("RDS group ");
		Logger.PrintLog(groupType);
		Logger.PrintLnLog((const char *)(versionB ? "B" : "A"));
	}

	// group 0A / 0B - Program Service name, 2 chars per group
	if(groupType == 0 && okD)
	{
		uint8_t index = (blockB & 0x03) * 2;

		char c1 = (char)(blockD >> 8);
		char c2 = (char)(blockD & 0xFF);

		RdsPS[index] = ((uint8_t)c1 >= 0x20) ? c1 : ' ';
		RdsPS[index + 1] = ((uint8_t)c2 >= 0x20) ? c2 : ' ';
	}

	// group 2A / 2B - RadioText
	if(groupType == 2)
	{
		uint8_t textAB = (blockB >> 4) & 0x01;

		// A/B flag changed -> new text, clear old one
		if(textAB != rdsTextAB)
		{
			memset(RdsRT, ' ', 64);
			RdsRT[64] = '\0';
			rdsTextAB = textAB;
		}

		uint8_t address = blockB & 0x0F;
		char chars[4];
		uint8_t count = 0;
		uint8_t index = 0;

		if(versionB == 0 && okC && okD)
		{
			// 2A: 4 chars per group, 64 chars text
			index = address * 4;
			chars[0] = (char)(blockC >> 8);
			chars[1] = (char)(blockC & 0xFF);
			chars[2] = (char)(blockD >> 8);
			chars[3] = (char)(blockD & 0xFF);
			count = 4;
		}
		else if(versionB == 1 && okD)
		{
			// 2B: 2 chars per group, 32 chars text
			index = address * 2;
			chars[0] = (char)(blockD >> 8);
			chars[1] = (char)(blockD & 0xFF);
			count = 2;
		}

		for(uint8_t i = 0; i < count; i++)
		{
			// 0x0D - end of text
			if(chars[i] == 0x0D)
			{
				RdsRT[index + i] = '\0';
				break;
			}

			RdsRT[index + i] = ((uint8_t)chars[i] >= 0x20) ? chars[i] : ' ';
		}
	}
}
