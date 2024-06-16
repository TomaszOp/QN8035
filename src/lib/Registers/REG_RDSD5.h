#ifndef _REG_RDSD5_H_
#define _REG_RDSD5_H_

#include "REGISTER.h"

	/*
	Word: RDSD5 Address: 10h (RW)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	rdsd5[7] rdsd5[6] rdsd5[5] rdsd5[4] rdsd5[3] rdsd5[2] rdsd5[1] rdsd5[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RDSD5 : public REGISTER
	{
		public:

		REG_RDSD5();
		~REG_RDSD5();
		
		
		/*
		RDS data byte 5
		
		7:0 
		RDSD5[7:0] 
		xxxxxxxx 
		*/
		uint8_t GetRDSD5();


		
		private: 


	}; 

#endif
