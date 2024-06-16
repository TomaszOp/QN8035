#ifndef _REG_INT_CTRL_H_
#define _REG_INT_CTRL_H_

#include "REGISTER.h"

	/*
	Word: INT_CTRL Address: 18h
	Bit 7 	(MSB) Bit 6 Bit 5 Bit 4 Bit 3 Bit 2 Bit 1 Bit 0 	(LSB)
	rds_int_en cca_int_en rds_only s1k_en rds_4k_en RSVD RSVD RSVD
	wo wo wo wo wo wo wo wo
	*/

	class REG_INT_CTRL : public REGISTER
	{
		public:

		REG_INT_CTRL();
		~REG_INT_CTRL();
		
		/*
		RDS RX interrupt enable. When RDS_INT_EN=1, a 4.5ms low pulse
		will be output from pad din (RX mode) when a new group data is
		received and stored into RDS0~RDS7 (RX mode).
		
		Rds_int_en Status
		0 0
		1 1
		
		Bit7 
		Symbo RDS_INT_EN 
		Default 0
		*/
		void SetRDS_INT_EN(uint8_t value);
		
		
		/*
		RX CCA interrupt enable. When CCA_INT_EN=1, a 4.5ms low pulse
		will be output from pad din (RX mode) when a RXCCA (RX mode) is
		finished.
		
		Cca_int_en Status
		0 Disable
		1 Enable
		
		Bit 6 
		Symbo CCA_INT_EN 
		Default 0
		*/
		void SetCH(uint8_t value);
		
		/*
		RDS mode, 
		
		rds_only RDS mode selection
		0 Received bit-stream have both RDS and MMBS blocks (‘E’ block)
		1 Received bit-stream has RDS block only, no MMBS block (‘E’ block)
		
		Bit 5 
		Symbol RDS_ONLY 
		Default 1
		*/
		void SetRDS_ONLY(uint8_t value);
		
		/*
		Internal 1K tone selection. It will be used as DAC output when RXREQ.
		
		0 Disable
		1 Enable
		
		Bit 4 
		Symbo S1K_EN 
		Default 0
		*/
		void SetS1K_EN(uint8_t value);
		
		
		/*
		Enable RDS 4k mode.
		
		Bit 3 
		Symbol RDS_4K_EN 
		Default 0 
		*/
		void SetRDS_4K_EN(uint8_t value);
		
		/*
		Reserved.
		
		Bit 2:0 
		Symbol RSVD 
		Default 000 
		*/
		void SetRSVD(uint8_t value);
		
		private: 


	}; 

#endif
