#include "Arduino.h"

#include "REG_CID1.h"

	REG_CID1::REG_CID1()
	{
		this->DataDefault = 0b00000001;
		this->Number = CID1;
	}

	REG_CID1::~REG_CID1() 
	{
	}

	uint8_t REG_CID1::GetCID0()
	{
		return (this->Data >> 5) & 0b00000111;
	}

	uint8_t REG_CID1::GetCID1()
	{
		return (this->Data >> 2) & 0b00000111;
	}

	uint8_t REG_CID1::GetCID2()
	{
		return this->Data  & 0b00000011;
	}
