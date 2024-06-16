#include "Arduino.h"

#include "REG_XTAL_DIV1.h"

	REG_XTAL_DIV1::REG_XTAL_DIV1()
	{
		this->DataDefault = 0b00001000;
		this->Number = XTAL_DIV1;
	}

	REG_XTAL_DIV1::~REG_XTAL_DIV1() 
	{
	}

	void REG_XTAL_DIV1::SetPLL_DLT(uint8_t value)
	{
		this->Data = (this->Data & 0b00000111) | (value << 3);
	}

	void REG_XTAL_DIV1::SetXTAL_DIV(uint8_t value)
	{
		this->Data = (this->Data & 0b11111000) | (value);
	}