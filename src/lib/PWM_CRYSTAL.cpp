#include "PWM_CRYSTAL.h"

	PWM_CRYSTAL::PWM_CRYSTAL()
	{
		this->Pin = DEFAULT_PWM_Pin;   
	}

	PWM_CRYSTAL::PWM_CRYSTAL(int _Pin)
	{
		AttachPWMPin(_Pin);
	}

	PWM_CRYSTAL::~PWM_CRYSTAL() 
	{
	}

	void PWM_CRYSTAL::AttachPWMPin(int _Pin)
	{    
		this->Pin = _Pin;   
	}
	
	void PWM_CRYSTAL::Start()
	{
		int pwmChannel = 0; // Selects channel 0
		int frequence = 32768; // PWM frequency 
		int resolution = 8; // bit resolution, 2 possible values
		int pwmPin = this->Pin;
		ledcSetup(pwmChannel, frequence, resolution);

		// Assigns the PWM channel to pin 
		ledcAttachPin(pwmPin, pwmChannel);

		// Create the selected output voltage
		ledcWrite(pwmChannel, 128); // 50%
	}

	void PWM_CRYSTAL::Stop()
	{
		int pwmChannel = 0; // Selects channel 0
		ledcWrite(pwmChannel, 0); // 50%
	}
	