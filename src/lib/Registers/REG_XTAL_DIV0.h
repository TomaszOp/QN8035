#ifndef _REG_XTAL_DIV0_H_
#define _REG_XTAL_DIV0_H_

#include "REGISTER.h"

	/*
	Word: XTAL_DIV0 Address: 15h
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	xtal_div[7] xtal_div[6] xtal_div[5] xtal_div[4] xtal_div[3] xtal_div[2] xtal_div[1] xtal_div[0]
	wo wo wo wo wo wo wo wo
	*/

	class REG_XTAL_DIV0 : public REGISTER
	{
		public:

		REG_XTAL_DIV0();
		~REG_XTAL_DIV0();
		
		/*
		Lower 8 bits of xtal_div[10:0].
		Xtal_div[10:0] = round(freq of xtal/32.768KHz)
		
		Bit 7:0 
		Symbol XTAL_DIV[7:0] 
		Default 00000001
		*/
		void SetXTAL_DIV(uint8_t value);
		
		private: 


	}; 

#endif
