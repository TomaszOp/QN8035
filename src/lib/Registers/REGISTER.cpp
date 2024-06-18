#include "Arduino.h"

#include "REGISTER.h"

	REGISTER::REGISTER()
	{
		debugSerial = false;
	}

	REGISTER::REGISTER(I2C *_i2c)
	{
		this->i2c = _i2c;
	}

	REGISTER::~REGISTER() 
	{
	}

	void REGISTER::RestoreData()
	{
		this->Data = DataDefault;
	}
	
	void REGISTER::SetI2C(I2C *_i2c)
	{
		this->i2c = _i2c;
	}

	void REGISTER::Write()
	{
		i2c->WriteRegister(this->Number, this->Data);
	}

	void REGISTER::Write(uint8_t _data)
	{
		this->Data = _data;
		Write();
	}
	
	uint8_t REGISTER::Read()
	{
		this->Data = i2c->ReadRegister(this->Number);
		
		return this->Data;
	}

	void REGISTER::SetData(uint8_t _data)
	{
		if(debugSerial)
		{
			Logger.PrintLog("Register: ");
			Logger.PrintLnLog(this->Number);

			Logger.PrintLog("Before: ");
			Logger.PrintLnLog(this->Data);
			Logger.PrintLnLogBin(this->Data);
			Logger.PrintLnLogHex(this->Data);

			Logger.PrintLog("After: ");
			Logger.PrintLnLog(_data);
			Logger.PrintLnLogBin(_data);
			Logger.PrintLnLogHex(_data);
		}

		this->Data = _data;
	}

	