#ifndef _REG_CH_STEP_H_
#define _REG_CH_STEP_H_

#include "REGISTER.h"

	/*
	CH_STEP Address: 0Ah
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	fstep[1] fstep[0] ch_stp[9] ch_stp[8] ch_sta[9] ch_sta[8] ch[9] ch[8]
	wo wo wo wo wo wo rw rw
	*/

	class REG_CH_STEP : public REGISTER
	{
		public:

		REG_CH_STEP();
		~REG_CH_STEP();
		
		/*
		CCA (channel scan) frequency step:
		00 50 kHz
		01 100 kHz
		10 200 kHz
		11 Reserved
		
		Bit 7:6 
		Symbol FSTEP[1:0]
		Default 01
		*/
		void SetFSTEP(uint8_t value);
		
		/*
		Highest 2 bits of 10-bit CCA (channel scan) stop channel index:
		Stop freq is (60+CH_STP*0.05) MHz.
		
		Bit 5:4
		Symbol CH_STP[9:8]
		Default 11
		*/
		void SetCH_STP(uint8_t value);
		
		/*
		Highest 2 bits of 10-bit CCA (channel scan) start channel index:
		Start freq is (60+CH_STA*0.05) MHz.
		
		Bit 3:2 
		Symbol CH_STA[9:8]
		Default 10 
		*/
		void SetCH_STA(uint8_t value);
		
		/*
		Highest 2 bits of 10-bit channel index:
		Channel freq is (60+CH*0.05) MHz.
		Bit 1:0 
		Symbol CH[9:8] 
		Default 10 
		*/
	    uint8_t GetCH();
		void SetCH(uint8_t value);

		private: 


	}; 

#endif
