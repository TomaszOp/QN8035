#include "Arduino.h"

#include "LoggerUart.h"

	LoggerUart::LoggerUart()
	{
		Enable = true;
	}

	LoggerUart::~LoggerUart() 
	{
	}

	void LoggerUart::PrintLog(const char * log)
	{
		if(!Enable) return;

		Serial.print(log);
	}

	void LoggerUart::PrintLnLog(const char * log)
	{
		if(!Enable) return;

		Serial.println(log);
	}

	void LoggerUart::PrintLog(uint8_t data)
	{
		if(!Enable) return;
		Serial.print(data);
	}

	void LoggerUart::PrintLnLog(uint8_t data)
	{
		if(!Enable) return;
		Serial.println(data);
	}

	void LoggerUart::PrintLog(float data)
	{
		if(!Enable) return;
		Serial.print(data);	
	}

	void LoggerUart::PrintLnLog(float data)
	{
		if(!Enable) return;
		Serial.println(data);
	}

	void LoggerUart::PrintLog(uint16_t data)
	{
		if(!Enable) return;
		Serial.print(data);	
	}

	void LoggerUart::PrintLnLog(uint16_t data)
	{
		if(!Enable) return;
		Serial.println(data);
	}

	void LoggerUart::PrintLogBin(uint8_t data)
	{
		if(!Enable) return;

		Serial.print("BIN ");
		Serial.print(data, BIN);
	}

	void LoggerUart::PrintLnLogBin(uint8_t data)
	{
		if(!Enable) return;

		Serial.print("BIN ");
		Serial.println(data, BIN);
	}

	void LoggerUart::PrintLogHex(uint8_t data)
	{
		if(!Enable) return;

		Serial.print("HEX ");
		Serial.print(data, HEX);
	}

	void LoggerUart::PrintLnLogHex(uint8_t data)
	{
		if(!Enable) return;
		
		Serial.print("HEX ");
		Serial.println(data, HEX);
	}