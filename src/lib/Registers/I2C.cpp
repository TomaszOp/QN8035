#include "I2C.h"

	I2C::I2C()
	{
		this->SdaPin = DEFAULT_SdaPin;   
		this->SclPin = DEFAULT_SclPin;  
	}

	I2C::I2C(int _sdaPin, int _sclPin, byte _address)
	{
		AttachI2CPins(_sdaPin, _sclPin);
		SetAddressI2C(_address);
	}

	I2C::~I2C() 
	{
	}

	void I2C::AttachI2CPins(int _sdaPin, int _sclPin)
	{    
		this->SdaPin = _sdaPin;   
		this->SclPin = _sclPin;      

		Wire.begin(this->SdaPin, this->SclPin);
		Wire.setClock(400000);
		Wire.setTimeOut(50000);
	}
	
	void I2C::SetAddressI2C(byte _address)
	{
		this->addressI2C = _address;
	}

	void I2C::PrintLog(const char * log)
	{
		if(debugSerial)
		Serial.println(log);
	}

	void I2C::PrintLog(int log)
	{
		if(debugSerial)
		Serial.println(log);
	}


	void I2C::WriteRegister(uint8_t registerNr, uint8_t _data)
	{
		PrintLog("WriteRegister");
		PrintLog(registerNr);
		PrintLog(_data);

		Wire.beginTransmission(this->addressI2C);

		delay(I2C_DELAY);
		Wire.write(registerNr);
		delay(I2C_DELAY);
		Wire.write(_data);
		delay(I2C_DELAY);
		Wire.endTransmission(true);

		delay(I2C_DELAY);
	}


	uint8_t I2C::ReadRegister(uint8_t registerNr)
	{
		PrintLog("ReadRegister");
		PrintLog(registerNr);
		//PrintLog(this->addressI2C);

		Wire.beginTransmission(this->addressI2C);
		Wire.write(registerNr);
		Wire.endTransmission();

		delay(I2C_DELAY);
		PrintLog("requestFrom");
        
		Wire.requestFrom(this->addressI2C, (int)1);
		
		delay(I2C_DELAY);

		byte data = 0;
		PrintLog("Wire.available");
		if (Wire.available())
		{
			data = Wire.read();
			PrintLog("Wire.read ");
			PrintLog(data);

			Wire.endTransmission(true);
		}

		delay(I2C_DELAY);
		return data;
	}