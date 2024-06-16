#include "Arduino.h"

#include "REG_RDSD1.h"

	REG_RDSD1::REG_RDSD1()
	{
		this->DataDefault = 0b00000000;
		this->Number = RDSD1;
	}

	REG_RDSD1::~REG_RDSD1() 
	{
	}

	uint8_t REG_RDSD1::GetRDSD1()
	{
		return this->Data;
	}