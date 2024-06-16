#include "Arduino.h"

#include "REG_RDSD3.h"

	REG_RDSD3::REG_RDSD3()
	{
		this->DataDefault = 0b00000000;
		this->Number = RDSD3;
	}

	REG_RDSD3::~REG_RDSD3() 
	{
	}

	uint8_t REG_RDSD3::GetRDSD3()
	{
		return this->Data;
	}