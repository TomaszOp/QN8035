#ifndef _REG_CH_STOP_H_
#define _REG_CH_STOP_H_

#include "REGISTER.h"

	/*
	Word: CH_STOP Address: 09h
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	ch_stp[7] ch_stp[6] ch_stp[5] ch_stp[4] ch_stp[3] ch_stp[2] ch_stp[1] ch_stp[0]
	wo wo wo wo wo wo wo wo
	*/

	class REG_CH_STOP : public REGISTER
	{
		public:

		REG_CH_STOP();
		~REG_CH_STOP();
		
		/*
		Lower 8 bits of 10-bit CCA (channel scan) stop channel index.
		
		Bit 7:0 
		Symbol CH_STP[7:0]
		Default 11000000
		*/
		void SetCH_STP(uint8_t value);

		private: 


	}; 

#endif
