#include "Arduino.h"

#include "REG_VOL_CTL.h"

	REG_VOL_CTL::REG_VOL_CTL()
	{
		this->DataDefault = 0b01000111;
		this->Number = VOL_CTL;
	}

	REG_VOL_CTL::~REG_VOL_CTL() 
	{
	}


	void REG_VOL_CTL::SetMUTE_EN(uint8_t value)
	{
		this->Data = (this->Data & 0b01111111) | (value << 7);
	}


	void REG_VOL_CTL::SetTC(uint8_t value)
	{
		this->Data = (this->Data & 0b10111111) | (value << 6);
	}

	void REG_VOL_CTL::SetGAIN_DIG(uint8_t value)
	{
		this->Data = (this->Data & 0b11000111) | (value << 3);
	}

	void REG_VOL_CTL::SetGAIN_ANA(uint8_t value)
	{
		this->Data = (this->Data & 0b11111000) | (value);
	}