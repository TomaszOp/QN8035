#include "Arduino.h"

#include "REG_CCA.h"

	REG_CCA::REG_CCA()
	{
		this->DataDefault = 0b01000000;
		this->Number = CCA;
		RestoreData();
	}

	REG_CCA::~REG_CCA() 
	{
	}


	void REG_CCA::SetXTAL_INJ(uint8_t value)
	{
		this->Data = (this->Data & 0b01111111) | (value << 7);
	}

	void REG_CCA::SetImr(uint8_t value)
	{
		this->Data = (this->Data & 0b10111111) | (value << 6);
	}

	uint8_t REG_CCA::GetImr()
	{
		return (this->Data >> 6) & 0b00000001;
	}

	void REG_CCA::SetXCCADL(uint8_t value)
	{
		this->Data = (this->Data & 0b11100000) | value ;
	}