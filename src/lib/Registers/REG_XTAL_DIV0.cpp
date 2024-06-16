#include "Arduino.h"

#include "REG_XTAL_DIV0.h"

	REG_XTAL_DIV0::REG_XTAL_DIV0()
	{
		this->DataDefault = 0b00000001;
		this->Number = XTAL_DIV0;
	}

	REG_XTAL_DIV0::~REG_XTAL_DIV0() 
	{
	}

	void REG_XTAL_DIV0::SetXTAL_DIV(uint8_t value)
	{
		this->Data = value;
	}