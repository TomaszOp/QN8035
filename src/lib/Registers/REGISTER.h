#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <stdint.h>

#include "Settings.h"
#include "I2C.h"
#include "LoggerUart.h"


	class REGISTER
	{
		public:

		REGISTER();
		REGISTER(I2C *_i2c);
		~REGISTER();
		
		uint8_t Data;
		uint8_t Number;

		I2C *i2c;

		void SetI2C(I2C *_i2c);

		void Write();
		void Write(uint8_t _data);
        uint8_t Read();

		void SetData(uint8_t _data);

		protected: 

        bool debugSerial;

		uint8_t DataDefault;

		void RestoreData();



		LoggerUart Logger;
	}; 

#endif
