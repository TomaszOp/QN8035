#include "Arduino.h"

#include "REG_STATUS2.h"

	REG_STATUS2::REG_STATUS2()
	{
		this->DataDefault = 0b00000000;
		this->Number = STATUS2;
	}

	REG_STATUS2::~REG_STATUS2() 
	{
	}


	uint8_t REG_STATUS2::GetRDS_RXTXUPD()
	{
		return (this->Data >> 7) & 0b00000001;
	}
		
	uint8_t REG_STATUS2::GetE_DET()
	{
		return (this->Data >> 6) & 0b00000001;
	}

	uint8_t REG_STATUS2::GetRDSC0C1()
	{
		return (this->Data >> 5) & 0b00000001;
	}

	uint8_t REG_STATUS2::GetRDSSYNC()
	{
		return (this->Data >> 4) & 0b00000001;
	}

	uint8_t REG_STATUS2::GetRDS0ERR()
	{
		return (this->Data >> 3) & 0b00000001;
	}

	uint8_t REG_STATUS2::GetRDS1ERR()
	{
		return (this->Data >> 2) & 0b00000001;
	}

	uint8_t REG_STATUS2::GetRDS2ERR()
	{
		return (this->Data >> 1) & 0b00000001;
	}

	uint8_t REG_STATUS2::GetRDS3ERR()
	{
		return (this->Data) & 0b00000001;
	}