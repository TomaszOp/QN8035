#ifndef _REG_CH_START_H_
#define _REG_CH_START_H_

#include "REGISTER.h"

	/*
	Word: CH_START Address: 08h
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	ch_sta[7] ch_sta[6] ch_sta[5] ch_sta[4] ch_sta[3] ch_sta[2] ch_sta[1] ch_sta[0]
	wo wo wo wo wo wo wo wo
	*/

	class REG_CH_START : public REGISTER
	{
		public:

		REG_CH_START();
		~REG_CH_START();
		
		/*
		Lower 8 bits of 10-bit CCA (channel scan) start channel index.
		
		Bit 7:0
		Symbol CH_STA[7:0] 
		Default 00011100 
		*/
		void SetCH_STA(uint8_t value);
		
		private: 


	}; 

#endif
