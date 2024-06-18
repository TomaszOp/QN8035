#ifndef _I2C_H_
#define _I2C_H_

#include "Arduino.h"
#include <Wire.h>


#define I2C_DELAY 3

#define DEFAULT_SdaPin 21
#define DEFAULT_SclPin 22

#define DEFAULT_i2C_ADDRESS 0x10

	class I2C
	{
		public:

		I2C();
		I2C(int _sdaPin, int _sclPin, byte _address);
		~I2C();
		
		int SdaPin;
		int SclPin;
		void AttachI2CPins(int _sdaPin, int _sclPin);
		void SetAddressI2C(byte _address);

        bool debugSerial;

		void WriteRegister(uint8_t registerNr, uint8_t _data);
        uint8_t ReadRegister(uint8_t registerNr);

		private: 

		byte addressI2C;

		void PrintLog(const char * log);
		void PrintLog(int log);
	}; 

#endif
