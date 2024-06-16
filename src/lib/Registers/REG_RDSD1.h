#ifndef _REG_RDSD1_H_
#define _REG_RDSD1_H_

#include "REGISTER.h"

	/*
	Word: RDSD1 Address: 0Ch (RW)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0
	(LSB) rdsd1[7] rdsd1[6] rdsd1[5] rdsd1[4] rdsd1[3] rdsd1[2] rdsd1[1] rdsd1[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RDSD1 : public REGISTER
	{
		public:

		REG_RDSD1();
		~REG_RDSD1();
		
		/*
		RDS data byte 1.
		
		7:0 
		RDSD1[7:0] 
		xxxxxxxx 
		*/
		uint8_t GetRDSD1();


		
		private: 


	}; 

#endif
