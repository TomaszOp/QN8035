#ifndef _REG_STATUS1_H_
#define _REG_STATUS1_H_

#include "REGISTER.h"

	/*
	Word: STATUS1 Address: 04h (RO)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	cap_sh fsm[2] fsm[1] fsm[0] rxcca_fail rxagcset rxagcerr st_mo_rx
	ro ro ro ro ro ro ro ro
	*/

	class REG_STATUS1 : public REGISTER
	{
		public:

		REG_STATUS1();
		~REG_STATUS1();
		
		/* 
		Reserved
		
		Bit 7 
		Symbol CAP_SH 
		Default r 
		*/
		uint8_t GetCAP_SH();
		
		/* 
		Top FSM state indicator:
		
		000 STBY
		001 RESET
		010 CALI
		011 IDLE
		100 CALIPLL
		101 RECEIVEING
		110 Reserved
		111 RXCCA

		Bit 6:4 
		Symbol FSM[2:0] 
		Default rrr
		*/
		uint8_t GetFSM();
		
		/* 
		RXCCA Status Flag: Indicates whether a valid channel is found during RX
		CCA. If a valid channel is found, channel index will stay there, and
		RXCCA_FAIL=0; otherwise, it will stay at the end of scan range and
		RXCCA_FAIL=1.

		0 RX CCA successful finds a valid channel.
		1 RX CCA fails to find a valid channel.

		Bit 3 
		Symbol RXCCA_FAIL 
		Default r
		*/
		uint8_t GetRXCCA_FAIL();
		
		/* 
		RX AGC settling status:
		
		0 Not Settled
		1 Settled

		Bit 2 
		Symbol RXAGCSET 
		Default r
		*/
		uint8_t GetRXAGCSET();
		
		/* 
		RXAGC status:
		
		0 No Error
		1 AGC Error

		Bit 1 
		Symbol RXAGCERR 
		Default r
		*/
		uint8_t GetRXAGCERR();
		
		/* 
		Stereo receiving status:

		1 Mono
		0 Stereo

		Bit 0 
		Symbol ST_MO_RX 
		Default r
		*/
		uint8_t GetST_MO_RX();


		
		private: 


	}; 

#endif
