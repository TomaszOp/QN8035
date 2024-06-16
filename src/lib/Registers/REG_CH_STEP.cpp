#include "Arduino.h"

#include "REG_CH_STEP.h"

	REG_CH_STEP::REG_CH_STEP()
	{
		this->DataDefault = 0b01111010;
		this->Number = CH_STEP;
	}

	REG_CH_STEP::~REG_CH_STEP() 
	{
	}

	void REG_CH_STEP::SetFSTEP(uint8_t value)
	{
		this->Data = (this->Data & 0b00111111) | (value << 6);
	}

	void REG_CH_STEP::SetCH_STP(uint8_t value)
	{
		this->Data = (this->Data & 0b11001111) | (value << 4);
	}

	void REG_CH_STEP::SetCH_STA(uint8_t value)
	{
		this->Data = (this->Data & 0b11110011) | (value << 2);
	}

	void REG_CH_STEP::SetCH(uint8_t value)
	{
		this->Data = (this->Data & 0b11111100) | (value);
	}

	uint8_t REG_CH_STEP::GetCH()
	{
		return this->Data & 0b00000011;
	}