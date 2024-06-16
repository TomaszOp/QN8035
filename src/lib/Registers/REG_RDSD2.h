#ifndef _REG_RDSD2_H_
#define _REG_RDSD2_H_

#include "REGISTER.h"

	/*
	Word: RDSD2 Address: 0Dh (RW)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0
	(LSB) rdsd2[7] rdsd2[6] rdsd2[5] rdsd2[4] rdsd2[3] rdsd2[2] rdsd2[1] rdsd2[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RDSD2 : public REGISTER
	{
		public:

		REG_RDSD2();
		~REG_RDSD2();
		
		/*
		RDS data byte 2
		
		7:0 
		RDSD2[7:0] 
		xxxxxxxx 
		*/
		uint8_t GetRDSD2();
		

		
		private: 


	}; 

#endif
