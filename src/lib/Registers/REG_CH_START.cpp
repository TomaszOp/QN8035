#include "Arduino.h"

#include "REG_CH_START.h"

	REG_CH_START::REG_CH_START()
	{
		this->DataDefault = 0b00011100;
		this->Number = CH_START;
	}

	REG_CH_START::~REG_CH_START() 
	{
	}

	void REG_CH_START::SetCH_STA(uint8_t value)
	{
		this->Data = value;
	}