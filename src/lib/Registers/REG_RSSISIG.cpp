#include "Arduino.h"

#include "REG_RSSISIG.h"

	REG_RSSISIG::REG_RSSISIG()
	{
		this->DataDefault = 0b01000000;
		this->Number = RSSISIG;
	}

	REG_RSSISIG::~REG_RSSISIG() 
	{
	}

	uint8_t REG_RSSISIG::GetRSSIDB()
	{
		return this->Data;
	}