#include "Arduino.h"

#include "REG_CH_STOP.h"

	REG_CH_STOP::REG_CH_STOP()
	{
		this->DataDefault = 0b11000000;
		this->Number = CH_STOP;
	}

	REG_CH_STOP::~REG_CH_STOP() 
	{
	}

	void REG_CH_STOP::SetCH_STP(uint8_t value)
	{
		this->Data= value;
	}
