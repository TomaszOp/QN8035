#include "Arduino.h"

#include "REG_STATUS1.h"

	REG_STATUS1::REG_STATUS1()
	{
		this->DataDefault = 0b00000000;
		this->Number = STATUS1;
		RestoreData();
	}

	REG_STATUS1::~REG_STATUS1() 
	{

	}

	uint8_t REG_STATUS1::GetCAP_SH()
	{
		return (this->Data >> 7) & 0b00000001;
	}
		
	uint8_t REG_STATUS1::GetFSM()
	{
		return (this->Data >> 4) & 0b00000111;
	}
	
	uint8_t REG_STATUS1::GetRXCCA_FAIL()
	{
		return (this->Data >> 3) & 0b00000001;
	}
	
	uint8_t REG_STATUS1::GetRXAGCSET()
	{
		return (this->Data >> 2) & 0b00000001;
	}
	
	uint8_t REG_STATUS1::GetRXAGCERR()
	{
		return (this->Data >> 1) & 0b00000001;
	}

	uint8_t REG_STATUS1::GetST_MO_RX()
	{
		return (this->Data) & 0b00000001;
	}
	