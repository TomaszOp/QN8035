#ifndef _REG_RDSD7_H_
#define _REG_RDSD7_H_

#include "REGISTER.h"

	/*
	Word: RDSD7 Address: 12h (RW)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	rdsd7[7] rdsd7[6] rdsd7[5] rdsd7[4] rdsd7[3] rdsd7[2] rdsd7[1] rdsd7[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RDSD7 : public REGISTER
	{
		public:

		REG_RDSD7();
		~REG_RDSD7();
		
		/*
		RDS data byte 7.
		
		7:0 
		RDSD7[7:0] 
		xxxxxxxx 
		*/
		uint8_t GetRDSD7();

		
		private: 


	}; 

#endif
