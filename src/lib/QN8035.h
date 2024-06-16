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

#define FREQ_TO_WORD(f) ((uint16_t)((f - 60) / 0.05))
#define WORD_TO_FREQ(w) (((float)w * 0.05) + 60)

/*
DEFAULT_SdaPin pin SDA
DEFAULT_SclPin pin SCL
DEFAULT_PWMPin pin Quatz if not exist real quartz
*/
	class QN8035
	{
		public:

		QN8035();
		~QN8035();
		
        bool debugSerial;

		/*
		conffigure output
		*/
		int SdaPin;
		int SclPin;
		void AttachI2CPins(int _sdaPin, int _sclPin);
		void SetAddressI2C(byte _address);
		void AttachPWMPin(int _pwmPin);

		void Init();

		/*
		chip registeres
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
		virtual quatrz
		*/
		PWM_CRYSTAL pwmCrystal;


		/*
		chip QN8035 method for users
		*/
		void TunerInit();
		uint8_t TunerShutdown();

		void SetFrequency(uint16_t frequency);
		void SetFrequencyMHz(float frequency);
		float GetFrequency();
		uint8_t Scan(ScanDirection direction);

		void SetVolume(uint8_t vale);
		uint16_t GetVolume(void);
		uint16_t SetVolume(VolumeDirection direction);
		void SetMute(bool value);

		int16_t GetSnr();
		int16_t GetRssi();

		void ScanFrequencyDown();
		void ScanFrequencyUp();

		void InitRDS();


		/*
		currently set parameters
		*/
		float FrequencyMHz;
		uint8_t Volume;
		bool Mute;


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


		void PrintLog(const char * log);
	}; 

#endif
