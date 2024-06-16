#ifndef _REG_VOL_CTL_H_
#define _REG_VOL_CTL_H_

#include "REGISTER.h"

	/*
	Word: VOL_CTL Address: 14h
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	mute_en tc gain_dig[2] gain_dig[1] gain_dig[0] gain_ana[2] gain_ana[1] gain_ana[0]
	wo wo wo wo wo wo wo wo
	*/

	class REG_VOL_CTL : public REGISTER
	{
		public:

		REG_VOL_CTL();
		~REG_VOL_CTL();
		
		/*
		RX audio Mute enable:

		0 No mute.
		1 Mute

		Bit 7 
		MUTE_EN 
		Default 0
		*/
		void SetMUTE_EN(uint8_t value);

		/*
		Pre-emphasis and de-emphasis time constant

		0 50 us
		1 75 us

		Bit 6 
		Symbol TC 
		Default 1
		*/
		void SetTC(uint8_t value);
		
		/*
		GAIN_DIG[2:0] set digital volume gain:

		101 -5 dB
		100 -4 dB
		011 -3 dB
		010 -2 dB
		001 -1 dB
		000 0 dB

		Bit 5:3 
		Symbol GAIN_DIG[2:0] 
		Default 000
		*/
		void SetGAIN_DIG(uint8_t value);
		
		/*
		Lower bits of GAIN_ANA[2:0]: Sets volume control gain of analog
		portion.

		111 0 dB
		110 -6 dB
		101 -12 dB
		100 -18 dB
		011 -24 dB
		010 -30 dB
		001 -36 dB
		000 -42 dB

		Bit 2:0 
		Symbol GAIN_ANA[2:0] 
		Default 111
		*/
		void SetGAIN_ANA(uint8_t value);
		
		
		private: 


	}; 

#endif
