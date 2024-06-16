#ifndef _PWM_CRYSTAL_H_
#define _PWM_CRYSTAL_H_

#include "Arduino.h"


#define DEFAULT_PWM_Pin 7


	class PWM_CRYSTAL
	{
		public:

		PWM_CRYSTAL();
		PWM_CRYSTAL(int _Pin);
		~PWM_CRYSTAL();
		
		int Pin;

		void AttachPWMPin(int _Pin);

		void Start();
		void Stop();

        bool debugSerial;

		private: 

	}; 

#endif
