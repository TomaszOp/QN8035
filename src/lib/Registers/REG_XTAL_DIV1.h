#ifndef _REG_XTAL_DIV1_H_
#define _REG_XTAL_DIV1_H_

#include "REGISTER.h"

	/*
	Word: XTAL_DIV1 Address: 16h
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	pll_dlt[4] pll_dlt[3] pll_dlt[2] pll_dlt[1] pll_dlt[0] xtal_div[10] xtal_div[9] xtal_div[8]
	wo wo wo wo wo wo wo wo
	*/

	class REG_XTAL_DIV1 : public REGISTER
	{
		public:

		REG_XTAL_DIV1();
		~REG_XTAL_DIV1();
		
		/*
		Lower 5 bits of pll_dlt[12:0]

		Bit 7:3 
		Symbol PLL_DLT[4:0] 
		Default 00001 
		*/
		void SetPLL_DLT(uint8_t value);
		
		/*
		Higher 3 bits of xtal_div[10:0].
		Xtal_div[10:0] = round(freq of xtal/32.768KHz)

		Bit 2:0 
		Symbol XTAL_DIV[10:8] 
		Default 000
		*/
		void SetXTAL_DIV(uint8_t value);
		
		private: 


	}; 

#endif
