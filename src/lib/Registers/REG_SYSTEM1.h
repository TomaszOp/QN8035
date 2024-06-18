#ifndef _REG_SYSTEM1_H_
#define _REG_SYSTEM1_H_

#include "REGISTER.h"

	/*
	Register SYSTEM1
	Bit 7 (MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 (LSB)
	swrst recal stnby rxreq rdsen force_mo chsc cca_ch_dis
	wo wo wo wo wo wo wo wo
	RO - Read Only: 
	WO - Write Only:
	R/W - Read/Write: 
	Typically, the value is set by the chip itself
	*/

	class REG_SYSTEM1 : public REGISTER
	{
		public:

		REG_SYSTEM1();
		~REG_SYSTEM1();
		


		/*
		Reset all registers to default values:
		
		0 Keep the current values
		1 Reset to the default values
		
		Bit 7 
		Symbol SWRST 
		Default 0
		*/
		void SetSWRST(uint8_t value);

		/*
		Reset the state to initial states and recalibrate all blocks:
		
		0 No reset. FSM runs normally.
		1 Reset the FSM. After this bit is de-asserted, FSM will go through all the power up and calibration sequence.
		
		Bit 6 
		Symbol RECAL 
		Default 0
		*/
		void SetRECAL(uint8_t value);

		/*
		Request immediately to enter Standby mode whatever the chip is in any states.
		Note: “stnby” has the highest priority.

		0 Non standby mode.
		1 Enter standby mode.
		
		Bit 5 
		Symbol STNBY 
		Default 0
		*/
		void SetSTNBY(uint8_t value);

		/*
		Receiving request (overwrites STNBY):
		
		0 Non RX mode. Either idle mode.
		1 Enter receive mode.
		Note: “stnby” must be set to “0” when entering RX mode.
		
		Bit 4 
		Symbol RXREQ 
		Default 0
		*/
		void SetRXREQ (uint8_t value);

		/*
		RDS enable:
		
		0 No RDS.
		1 RDS enable.
		
		Bit 3 
		Symbol RDSEN 
		Default 0
		*/
		void SetRDSEN(uint8_t value);

		/*
		Force receiver in MONO mode:
		
		0 Not forced. ST/MONO auto selected
		1 Forced in MONO mode
		
		Bit 2 
		Symbol FORCE_MO 
		Default 0
		*/
		void SetFORCE_MO(uint8_t value);

		/*
		Channel Scan mode enable: Combined with RXREQ, chip scans for
		occupied channel for receiving. After completing channel scanning, this bit
		will be cleared automatically.
		For RX Scan, the FIRST valid channel will be selected. To start CCA, set
		QN8035
		Rev 0.08 (02/10) Copyright ©2010 by Quintic Corporation Page 20
		Confidential A Confidential Information contained herein is covered under Non-Disclosure Agreement (NDA).
		Advance Technical Information. This is a product under development. Characteristics and specifications are subject to change without notice.
		CHSC (REG0 [1]) =1. CHSC will be reset automatically when CCA is
		complete. To use the scanned channel, set CCA_CH_DIS=0.
		(CCA_CH_DIS can be set to 0 at the same time CHSC=1).
		
		0 Normal operation
		1 Channel Scan mode operation.
		
		Bit 1 
		Symbol CHSC 
		Default 0
		*/
		void SetCHSC(uint8_t value);

		/*
		CH (channel index) selection method: See description for CH register at
		07h and 0Ah for more information.
		 
		0 CH is determined by internal CCA (channel scan).
		1 CH is determined by the content in CH [9:0].
		
		Bit 0 
		Symbol CCA_CH_DIS 
		Default 1
		*/
		void SetCCA_CH_DIS(uint8_t value);


		uint8_t SWRST;
		uint8_t RECAL;
		uint8_t STNBY;
		uint8_t RXREQ;
		uint8_t RDSEN;
		uint8_t FORCE_MO;
		uint8_t CHSC;
		uint8_t CCA_CH_DIS;


		private: 


	}; 

#endif
