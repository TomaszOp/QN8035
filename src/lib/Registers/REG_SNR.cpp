#include "Arduino.h"

#include "REG_SNR.h"

	REG_SNR::REG_SNR()
	{
		this->DataDefault = 0b00000000;
		this->Number = SNR;
	}

	REG_SNR::~REG_SNR() 
	{
	}

	uint8_t REG_SNR::GetSNRDB()
	{
		return this->Data;
	}