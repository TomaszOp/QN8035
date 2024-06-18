#ifndef _REG_CCA_H_
#define _REG_CCA_H_

#include "REGISTER.h"

	/*
	Word: CCA Address: 01h
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	XTAL_INJ imr rxccad[5] rxccad[4] rxccad[3] rxccad[2] rxccad[1] rxccad[0]
	wo rw wo wo wo wo wo wo
	RO - Read Only: 
	WO - Write Only:
	R/W - Read/Write: 
	Typically, the value is set by the chip itself
	*/

	class REG_CCA : public REGISTER
	{
		public:

		REG_CCA();
		~REG_CCA();
		
		/*
		Select the reference clock source
		
		0 Inject sine-wave clock
		1 Inject digital clock
		
		Bit 7 
		Symbol XTAL_INJ 
		Default 01
		*/
		uint8_t SetXTAL_INJ(uint8_t value);

		/*
		Image Rejection. In CCA disabled mode (CCA_DIS=1), this is user set value. In
		CCA mode, this is CCA selection read out
		
		0 LO<RF, image is in lower side
		1 LO>RF, image is in upper side
		
		Bit 6 
		Symbol imr 
		Default 0
		*/
		void SetImr(uint8_t value);
		uint8_t GetImr();

		/*
		RXCCAD [5:0] is used to set the threshold for RX CCA. Channel with RSSI
		(dBuV) > (RXCCAD-10) dBuv is selected as valid channel.
		
		Bit 5:0 
		Symbol RXCCAD[5:0] 
		Default 000000
		*/
		void SetXCCADL(uint8_t value);
		
		private: 


	}; 

#endif
