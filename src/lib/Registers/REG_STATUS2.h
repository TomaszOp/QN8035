#ifndef _REG_STATUS2_H_
#define _REG_STATUS2_H_

#include "REGISTER.h"

	/*
	Word: STATUS2 Address: 13h (RO)
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	rds_rxtxupd e_det rdsc0c1 rdssync rdsd0err rdsd1err rdsd2err rdsd3err
	ro ro ro ro ro ro ro ro
	*/

	class REG_STATUS2 : public REGISTER
	{
		public:

		REG_STATUS2();
		~REG_STATUS2();
		
		/*
		RDS RX: RDS received group updated. Each time a new group is
		received, this bit will be toggled.
		If RDS_INT_EN=1, then at the same time this bit is toggled, the interrupt
		output pin (INT) will output a 4.5 ms low pulse.

		0->1 or 1->0 A new set (8 bytes) of data is received.
		0->0 or 1->1 New data is in receiving.

		Bit 7 
		Symbol RDS_RXTXUPD 
		Default r
		*/
		uint8_t GetRDS_RXTXUPD();
		
		/*
		‘E’ block (MMBS block) detected:
		
		0 Not Detected
		1 Detected

		Bit 6 
		Symbol E_DET 
		Default r
		*/
		uint8_t GetE_DET();
		
		/*
		Type indicator of the RDS third block in one group:
		
		0 C0
		1 C1

		Bit 5 
		Symbol RDSC0C1 
		Default r
		*/
		uint8_t GetRDSC0C1();
		
		/*
		RDS block synchronous indicator:
		
		0 Non-synchronous
		1 Synchronous

		Bit 4 
		Symbol RDSSYNC 
		Default r
		*/
		uint8_t GetRDSSYNC();
		
		/*
		Received RDS block 0 status indicator:
		
		0 No Error
		1 Error

		Bit 3 
		Symbol RDS0ERR 
		Default r
		*/
		uint8_t GetRDS0ERR();
		
		/*
		Received RDS block 1 status indicator:
		
		0 No Error
		1 Erro

		Bit 2 
		Symbol RDS1ERR 
		Default r
		*/
		uint8_t GetRDS1ERR();
		
		/*
		Received RDS block 2 status indicator:

		0 No Error
		1 Error

		Bit 1 
		Symbol RDS2ERR 
		Default r
		*/
		uint8_t GetRDS2ERR();
		
		/*
		Received RDS block 3 status indicator:
		
		0 No Error
		1 Error

		Bit 0 
		Symbol RDS3ERR 
		Default r
		*/
		uint8_t GetRDS3ERR();
		
		private: 


	}; 

#endif
