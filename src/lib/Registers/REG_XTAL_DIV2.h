#ifndef _REG_XTAL_DIV2_H_
#define _REG_XTAL_DIV2_H_

#include "REGISTER.h"

	/*
	Word: XTAL _DIV2 Address: 17h
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	pll_dlt[12] pll_dlt[11] pll_dlt[10] pll_dlt[9] pll_dlt[8] pll_dlt[7] pll_dlt[6] pll_dlt[5]
	wo wo wo wo wo wo wo wo
	*/

	class REG_XTAL_DIV2 : public REGISTER
	{
		public:

		REG_XTAL_DIV2();
		~REG_XTAL_DIV2();
		
		/*
		Higher 8 bits of pll_dlt[12:0].
		Pll_dlt[12:0] = round (28.5MHz / (Freqxtal/xtal_div[10:0]/512) ) - 442368 .

		Bit 7:0 
		Symbol PLL_DLT[12:5] 
		Default 01011100 
		*/
		void SetPLL_DLT(uint8_t value);
		
		private: 


	}; 

#endif
