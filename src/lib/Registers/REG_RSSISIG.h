#ifndef _REG_RSSISIG_H_
#define _REG_RSSISIG_H_

#include "REGISTER.h"

	/*
	Word: RSSISIG Address: 03h (RO)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	rssidb[7] rssidb[6] rssidb[5] rssidb[4] rssidb[3] rssidb[2] rssidb[1] rssidb[0]
	ro ro ro ro ro ro ro ro
	*/

	class REG_RSSISIG : public REGISTER
	{
		public:

		REG_RSSISIG();
		~REG_RSSISIG();
		
		/*
		In-band signal RSSI (Received Signal Strength Indicator) dBμV value:
		dBμV = RSSI (with AGC correction) - 43

		7:0 
		RSSIDB[7:0] 
		rrrr rrrr
		*/
		uint8_t GetRSSIDB();
		
		private: 


	}; 

#endif
