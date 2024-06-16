#ifndef _REG_RDSD0_H_
#define _REG_RDSD0_H_

#include "REGISTER.h"

	/*
	Word: RDSD1 Address: 0Ch (RW)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	rdsd0[7] rdsd0[6] rdsd0[5] rdsd0[4] rdsd0[3] rdsd0[2] rdsd0[1] rdsd0[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RDSD0 : public REGISTER
	{
		public:

		REG_RDSD0();
		~REG_RDSD0();
		
		/*
		RDS data byte 1.
		Default xxxxxxxx
		7:0 RDSD1[7:0] 
		*/
		uint8_t GetRDSD0();
		

		
		private: 


	}; 

#endif
