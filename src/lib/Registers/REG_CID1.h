#ifndef _REG_CID1_H_
#define _REG_CID1_H_

#include "REGISTER.h"

	/*
	Word: CID1 Address: 05h (RO)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	cid0[2] cid0[1] cid0[0] cid1[2] cid1[1] cid1[0] cid2[1] cid2[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_CID1 : public REGISTER
	{
		public:

		REG_CID1();
		~REG_CID1();
		
		/*
		reserved
		
		Bit 7:5 
		Symbol CID0[2:0] 
		value rrr 
		*/
		uint8_t GetCID0();
		
		/*
		Chip ID for product family:
		
		000 FM
		001~111 Reserved

		Bit 4:2 
		Symbol CID1[2:0] 

		value rrr
		value 000

		*/
		uint8_t GetCID1();
		
		/*
		Chip ID for minor revision:
		
		00 1
		01 2
		10 3
		11 4

		Bit 1:0 
		Symbol CID2[1:0] 
		value rr
		value 01
		*/
		uint8_t GetCID2();

		private: 


	}; 

#endif
