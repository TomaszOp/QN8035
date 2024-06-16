#include "Arduino.h"

#include "REG_RDSD5.h"

	REG_RDSD5::REG_RDSD5()
	{
		this->DataDefault = 0b00000000;
		this->Number = RDSD5;
	}

	REG_RDSD5::~REG_RDSD5() 
	{
	}

	uint8_t REG_RDSD5::GetRDSD5()
	{
		return this->Data;
	}