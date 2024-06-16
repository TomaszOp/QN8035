#include "Arduino.h"

#include "REG_XTAL_DIV2.h"

	REG_XTAL_DIV2::REG_XTAL_DIV2()
	{
		this->DataDefault = 0b01011100;
		this->Number = XTAL_DIV2;
	}

	REG_XTAL_DIV2::~REG_XTAL_DIV2() 
	{
	}

	void REG_XTAL_DIV2::SetPLL_DLT(uint8_t value)
	{
		this->Data = value;
	}

