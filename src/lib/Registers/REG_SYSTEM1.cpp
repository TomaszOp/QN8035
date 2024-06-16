#include "Arduino.h"

#include "REG_SYSTEM1.h"

	REG_SYSTEM1::REG_SYSTEM1()
	{
		this->DataDefault = 0b00000001;
		this->Number = SYSTEM1;
		RestoreData();
	}

	REG_SYSTEM1::~REG_SYSTEM1() 
	{
	}

	void REG_SYSTEM1::SetSWRST(uint8_t value)
	{
		this->SetData((this->Data & 0b01111111) | (value << 7));
	}

	void REG_SYSTEM1::SetRECAL(uint8_t value)
	{
		this->Data = (this->Data & 0b10111111) | (value << 6);
	}

	void REG_SYSTEM1::SetSTNBY(uint8_t value)
	{
		this->Data = (this->Data & 0b11011111) | (value << 5);
	}

	void REG_SYSTEM1::SetRXREQ (uint8_t value)
	{
		this->Data = (this->Data & 0b11101111)  | (value << 4);
	}

	void REG_SYSTEM1::SetRDSEN(uint8_t value)
	{
		this->Data = (this->Data & 0b11110111) | (value << 3);
	}

	void REG_SYSTEM1::SetFORCE_MO(uint8_t value)
	{
		this->Data = (this->Data & 0b11111011) | (value << 2);
	}

	void REG_SYSTEM1::SetCHSC(uint8_t value)
	{
		this->Data = (this->Data & 0b11111101) | (value << 1);
	}

	void REG_SYSTEM1::SetCCA_CH_DIS(uint8_t value)
	{
		this->Data = (this->Data & 0b11111110) | value;
	}