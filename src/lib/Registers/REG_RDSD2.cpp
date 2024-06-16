#include "Arduino.h"

#include "REG_RDSD2.h"

	REG_RDSD2::REG_RDSD2()
	{
		this->DataDefault = 0b00000000;
		this->Number = RDSD2;
	}

	REG_RDSD2::~REG_RDSD2() 
	{
	}

	uint8_t REG_RDSD2::GetRDSD2()
	{
		return this->Data;
	}