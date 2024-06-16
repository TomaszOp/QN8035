#include "Arduino.h"

#include "REG_CH.h"

	REG_CH::REG_CH()
	{
		this->DataDefault = 0b00110000;
		this->Number = CH;
	}

	REG_CH::~REG_CH() 
	{
	}

	uint8_t REG_CH::GetCH()
	{
		return this->Data;
	}

	void REG_CH::SetCH(uint8_t value)
	{
		this->Data = value;
	}
