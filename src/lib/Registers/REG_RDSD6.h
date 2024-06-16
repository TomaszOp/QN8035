#ifndef _REG_RDSD6_H_
#define _REG_RDSD6_H_

#include "REGISTER.h"

	/*
	Word: RDSD6 Address: 11h (RW)
	Bit 7(MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	rdsd6[7] rdsd6[6] rdsd6[5] rdsd6[4] rdsd6[3] rdsd6[2] rdsd6[1] rdsd6[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RDSD6 : public REGISTER
	{
		public:

		REG_RDSD6();
		~REG_RDSD6();
		
		
		/*
		RDS data byte 6.
		
		7:0 
		RDSD6[7:0] 
		xxxxxxxx 
		*/
		uint8_t GetRDSD6();

		
		private: 


	}; 

#endif
