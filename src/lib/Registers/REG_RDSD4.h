#ifndef _REG_RDSD4_H_
#define _REG_RDSD4_H_

#include "REGISTER.h"

	/*
	Word: RDSD4 Address: 0Fh (RW)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	rdsd4[7] rdsd4[6] rdsd4[5] rdsd4[4] rdsd4[3] rdsd4[2] rdsd4[1] rdsd4[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RDSD4 : public REGISTER
	{
		public:

		REG_RDSD4();
		~REG_RDSD4();
		
		
		/*
		RDS data byte 4
		
		7:0 
		RDSD4[7:0] 
		xxxxxxxx 
		*/
		uint8_t GetRDSD4();


		
		private: 


	}; 

#endif
