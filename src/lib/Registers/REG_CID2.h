#ifndef _REG_CID2_H_
#define _REG_CID2_H_

#include "REGISTER.h"

	/*
	Word: CID2 Address: 06h (RO)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	cid3[5] cid3[4] cid3[3] cid3[2] cid3[1] cid3[0] cid4[1] cid4[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_CID2 : public REGISTER
	{
		public:

		REG_CID2();
		~REG_CID2();
		
		/*
		Chip ID for product ID:
		
		0000-0111 Reserved
		100001 QN8035
		100001-111111 Reserved

		Bit 7:2 
		Symbol CID3[5:0] 
		Devault rrrrrr
		Devault 100001
		*/
		uint8_t GetCID3();
		
		/*
		Chip ID for major revision is 1+CID4
		
		00 1
		01 2
		10 3
		11 4

		Bit 1:0 
		Symbol CID4[3:0] 
		Devault rrrr
		Devault 00
		*/
		uint8_t GetCID4();

		private: 


	}; 

#endif
