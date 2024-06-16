#include "Arduino.h"

#include "REG_CID2.h"

	REG_CID2::REG_CID2()
	{
		this->DataDefault = 0b10000100;
		this->Number = CID2;
	}

	REG_CID2::~REG_CID2() 
	{
	}

	uint8_t REG_CID2::GetCID3()
	{
		return (this->Data >> 2) & 0b00111111;
	}

	uint8_t REG_CID2::GetCID4()
	{
		return this->Data  & 0b00000011;
	}