#include "Arduino.h"

#include "REG_INT_CTRL.h"

	REG_INT_CTRL::REG_INT_CTRL()
	{
		this->DataDefault = 0b00100000;
		this->Number = INT_CTRL;
	}

	REG_INT_CTRL::~REG_INT_CTRL() 
	{
	}

	void REG_INT_CTRL::SetRDS_INT_EN(uint8_t value) 
	{
		this->Data = (this->Data & 0b01111111) | (value << 7);
	}
		
	void REG_INT_CTRL::SetCH(uint8_t value) 
	{
		this->Data = (this->Data & 0b110111111) | (value << 6);
	}
	
	void REG_INT_CTRL::SetRDS_ONLY(uint8_t value) 
	{
		this->Data = (this->Data & 0b11011111) | (value << 5);
	}

	void REG_INT_CTRL::SetS1K_EN(uint8_t value) 
	{
		this->Data = (this->Data & 0b11101111) | (value << 4);
	}
	
	void REG_INT_CTRL::SetRDS_4K_EN(uint8_t value) 
	{
		this->Data = (this->Data & 0b11110111) | (value << 3);
	}
	
	void REG_INT_CTRL::SetRSVD(uint8_t value) 
	{
		this->Data = (this->Data & 0b11111000) | (value);
	}
