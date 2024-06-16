#ifndef _REG_RDSD3_H_
#define _REG_RDSD3_H_

#include "REGISTER.h"

	/*
	Word: RDSD3 Address: 0Eh (RW)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0
	(LSB) rdsd3[7] rdsd3[6] rdsd3[5] rdsd3[4] rdsd3[3] rdsd3[2] rdsd3[1] rdsd3[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RDSD3 : public REGISTER
	{
		public:

		REG_RDSD3();
		~REG_RDSD3();
		
		/*
		RDS data byte 3.
		
		7:0 
		RDSD3[7:0] 
		xxxxxxxx 
		*/
		uint8_t GetRDSD3();


		
		private: 


	}; 

#endif
