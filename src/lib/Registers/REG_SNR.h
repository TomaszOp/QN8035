#ifndef _REG_SNR_H_
#define _REG_SNR_H_

#include "REGISTER.h"

	/*
	Word: SNR Address: 02h
	Bit 7(MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0(LSB)
	rssidb[7] rssidb[6] rssidb[5] rssidb[4] rssidb[3] rssidb[2] rssidb[1] rssidb[0]
	ro ro ro ro ro ro ro ro
	RO - Read Only: 
	WO - Write Only:
	R/W - Read/Write: 
	Typically, the value is set by the chip itself
	*/

	class REG_SNR : public REGISTER
	{
		public:

		REG_SNR();
		~REG_SNR();
		
		/*
		In band signal to noise ratio.
		
		Bit 7:0 
		Symbol SNRDB 
		Default rrrrrrrr 
		*/
		uint8_t GetSNRDB();

		
		private: 


	}; 

#endif
