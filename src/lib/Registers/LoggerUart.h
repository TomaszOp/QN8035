#ifndef _LoggerUart_H_
#define _LoggerUart_H_

#include <stdint.h>

	class LoggerUart
	{
		public:

		LoggerUart();
		~LoggerUart();



		void PrintLog(const char * log);
		void PrintLnLog(const char * log);

		void PrintLog(uint8_t data);
		void PrintLnLog(uint8_t data);

		void PrintLog(uint16_t data);
		void PrintLnLog(uint16_t data);



		void PrintLogBin(uint8_t data);
		void PrintLnLogBin(uint8_t data);
		
		void PrintLogHex(uint8_t data);
		void PrintLnLogHex(uint8_t data);

		void PrintLog(float data);
		void PrintLnLog(float data);

		bool Enable;

		protected: 



	}; 

#endif
