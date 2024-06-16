#include "Arduino.h"

#include "REG_RDSD0.h"

	REG_RDSD0::REG_RDSD0()
	{
		this->DataDefault = 0b00000000;
		this->Number = RDSD0;
	}

	REG_RDSD0::~REG_RDSD0() 
	{
	}

	uint8_t REG_RDSD0::GetRDSD0()
	{
		return this->Data;
	}