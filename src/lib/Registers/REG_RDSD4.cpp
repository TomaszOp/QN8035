#include "Arduino.h"

#include "REG_RDSD4.h"

	REG_RDSD4::REG_RDSD4()
	{
		this->DataDefault = 0b00000000;
		this->Number = RDSD4;
	}

	REG_RDSD4::~REG_RDSD4() 
	{
	}

	uint8_t REG_RDSD4::GetRDSD4()
	{
		return this->Data;
	}