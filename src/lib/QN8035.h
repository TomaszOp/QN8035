#ifndef _QN8035_H_
#define _QN8035_H_

#include <Wire.h>

#include "Registers/REG_SYSTEM1.h"
#include "Registers/REG_CCA.h"
#include "Registers/REG_SNR.h"
#include "Registers/REG_RSSISIG.h"
#include "Registers/REG_STATUS1.h"
#include "Registers/REG_CID1.h"
#include "Registers/REG_CID2.h"
#include "Registers/REG_CH.h"
#include "Registers/REG_CH_START.h"
#include "Registers/REG_CH_STOP.h"
#include "Registers/REG_CH_STEP.h"
#include "Registers/REG_RDSD0.h"
#include "Registers/REG_RDSD1.h"
#include "Registers/REG_RDSD2.h"
#include "Registers/REG_RDSD3.h"
#include "Registers/REG_RDSD4.h"
#include "Registers/REG_RDSD5.h"
#include "Registers/REG_RDSD6.h"
#include "Registers/REG_RDSD7.h"
#include "Registers/REG_STATUS2.h"
#include "Registers/REG_VOL_CTL.h"
#include "Registers/REG_XTAL_DIV0.h"
#include "Registers/REG_XTAL_DIV1.h"
#include "Registers/REG_XTAL_DIV2.h"
#include "Registers/REG_INT_CTRL.h"

#include "PWM_CRYSTAL.h"



#define DEFAULT_SdaPin 21
#define DEFAULT_SclPin 22

#define DEFAULT_i2C_ADDRESS 0x10

#define DEFAULT_PWMPin 7

#define FREQ_TO_WORD(f) ((uint16_t)(((f) - 60) / 0.05 + 0.5))
#define WORD_TO_FREQ(w) (((float)w * 0.05) + 60)

/*
DEFAULT_SdaPin pin SDA
DEFAULT_SclPin pin SCL
DEFAULT_PWMPin pin Quatz if not exist real quartz, add resistor 10k to PWMPin and XCLK
*/
	class QN8035
	{
		public:

		QN8035();
		~QN8035();
		
        bool debug;


		/*
		conffigure output
		*/
		int SdaPin;
		int SclPin;
		void AttachI2CPins(int _sdaPin, int _sclPin);
		void SetAddressI2C(byte _address);
		void AttachPWMPin(int _pwmPin);


		/*
		chip registers
		*/
		REG_SYSTEM1 system1;
		REG_CCA cca;
		REG_SNR snr;
		REG_RSSISIG rssisig;
		REG_STATUS1 status1;
		REG_CID1 cid1;
		REG_CID2 cid2; 
		REG_CH ch;
		REG_CH_START ch_start;
		REG_CH_STOP ch_stop;
		REG_CH_STEP ch_step;
		REG_RDSD0 rdsd0;
		REG_RDSD1 rdsd1;
		REG_RDSD2 rdsd2;
		REG_RDSD3 rdsd3;
		REG_RDSD4 rdsd4;
		REG_RDSD5 rdsd5;
		REG_RDSD6 rdsd6;
		REG_RDSD7 rdsd7;
		REG_STATUS2 rdsstatus2;
		REG_VOL_CTL vol_ctl;
		REG_XTAL_DIV0 xtadiv0;
		REG_XTAL_DIV1 xtadiv1;
		REG_XTAL_DIV2 xtadiv2;
		REG_INT_CTRL int_ctrl;

		/*
		module i2C communications
		*/
		I2C i2c;

		/*
		virtual quartz
		*/
		PWM_CRYSTAL pwmCrystal;


		/*
		chip QN8035 method for users
		*/
		void TunerInit();

		void SetStandby(bool value);

		void SetFrequency(uint16_t frequency);
		void SetFrequencyMHz(float frequency);
		float GetFrequencyMHz();
		
		float Scan(ScanDirection direction);

		void SetVolumeA(uint8_t vale);
		uint8_t GetVolumeA(void);
		uint8_t SetVolumeA(VolumeDirection direction);

		/*
		full volume 0 - 47 in 1 dB steps (47 = 0 dB, 0 = -47 dB)
		uses GAIN_ANA (6 dB steps) and GAIN_DIG (1 dB steps)
		*/
		void SetVolume(uint8_t level);
		uint8_t SetVolume(VolumeDirection direction);
		uint8_t GetVolume(void);
		void SetMute(bool value);

		/*
		SetMono(true) forces mono output (FORCE_MO), false = auto stereo / mono
		IsStereo() reads from chip whether the station is received in stereo (ST_MO_RX)
		*/
		void SetMono(bool value);
		bool GetMono();
		bool IsStereo();

		void SetWaveClockType(CCA__XTAL_INJ value);

		/*
		internal 1 kHz test tone on the audio output (S1K_EN), for testing the audio path
		works in RX mode (chip not in standby), replaces the received audio
		volume and mute settings still apply
		*/
		void SetTestTone(bool value);
		bool GetTestTone();


		int8_t GetSnr();
		int8_t GetRssi();

		float ScanFrequencyDown();
		float ScanFrequencyUp();

		/*
		scan frequency step, used by ScanFrequencyUp / ScanFrequencyDown
		*/
		void SetScanStep(CH_STEP__FSTEP step);
		CH_STEP__FSTEP GetScanStep();

		/*
		scan threshold RXCCAD (0 - 63), channel is valid if RSSI (dBuV) > (level - 10)
		default DEFAULT_CCA_LEVEL
		*/
		void SetCCALevel(uint8_t level);
		uint8_t GetCCALevel();

		/*
		RDS
		InitRDS() enables RDS on the current station,
		ReadRDS() must be called often (every < 80 ms), returns true when a new valid group was decoded.
		*/
		void InitRDS();
		void SetRDS(bool value);
		bool ReadRDS();
		void ClearRDS();

		bool RdsEnabled;
		bool RdsSync;
		uint16_t RdsPI;       // Program Identification
		uint8_t RdsPTY;       // Program Type
		char RdsPS[9];        // Program Service name, 8 chars
		char RdsRT[65];       // RadioText, up to 64 chars


		/*
		currently set parameters
		*/
		float FrequencyMHz;
		uint16_t FrequencyCurrent;

		uint8_t Volume;
		uint8_t VolumeFull;
		CH_STEP__FSTEP ScanStep;
		uint8_t CCALevel;
		bool Mute;
		bool Mono;
		bool TestTone;


		/*
		only for testing
		*/
		void StartPWMCrystal(int _Pin);
		void StartPWMCrystal();
		void StopPWMCrystal();

		void TunerTest();
		void TunerTest2();



		private: 

		byte addressI2C;
		LoggerUart Logger;

		/*
		only for testing, send data to i2c without registerr class
		*/
		void WriteRegister(uint8_t registerNr, uint8_t _data);
        uint8_t ReadRegister(uint8_t registerNr);

		float Scan(float freqStartMhz, float freqEndMhz);
		float CheckScanComplete();

		uint8_t rdsLastUpdate;
		uint8_t rdsTextAB;
		void DecodeRDS(uint16_t blockA, uint16_t blockB, uint16_t blockC, uint16_t blockD, uint8_t errors);
	}; 

#endif
