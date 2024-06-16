#ifndef _REG_CH_H_
#define _REG_CH_H_

#include "REGISTER.h"

	/*
	Word: CH Address: 07h (RW)
	Bit 7 	(MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 	(LSB)
	ch[7] ch[6] ch[5] ch[4] ch[3] ch[2] ch[1] ch[0]
	rw rw rw rw rw rw rw rw
	*/

	class REG_CH : public REGISTER
	{
		public:

		REG_CH();
		~REG_CH();
		
		
		/*
		Lower 8 bits of 10-bit Channel index. Channel used for RX has two
		origins, one is from CH register (REG 07h+REG 0Ah [1:0]), which can
		be written by the user, another is from CCA/CCS. CCA/CCS selected
		channel is stored in an internal register, which is physically a different
		register with CH register, but it can be read out through register CH and
		be used for RX when CCA_CH_DIS(REG0[0])=0.
		FM channel: (60+CH*0.05)MHz
		
		Bit 7:0 
		Symbol CH[7:0]
		Default 00110000
		*/
		uint8_t GetCH();
		void SetCH(uint8_t value);
		
		private: 


	}; 

#endif
