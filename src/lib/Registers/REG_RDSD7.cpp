#include "Arduino.h"

#include "REG_RDSD7.h"

	REG_RDSD7::REG_RDSD7()
	{
		this->DataDefault = 0b00000000;
		this->Number = RDSD7;
	}

	REG_RDSD7::~REG_RDSD7() 
	{
	}

	uint8_t REG_RDSD7::GetRDSD7()
	{
		return this->Data;
	}