#include "Arduino.h"

#include "REG_RDSD6.h"

	REG_RDSD6::REG_RDSD6()
	{
		this->DataDefault = 0b00000000;
		this->Number = RDSD6;
	}

	REG_RDSD6::~REG_RDSD6() 
	{
	}

	uint8_t REG_RDSD6::GetRDSD6()
	{
		return this->Data;
	}