#include "PWM_CRYSTAL.h"
#include "driver/ledc.h"

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
		//int frequence = 4000000; // PWM frequency 
		int resolution = 8; // bit resolution, 2 possible values
		int pwmPin = this->Pin;
		ledcSetup(pwmChannel, frequence, resolution);

		// Assigns the PWM channel to pin 
		ledcAttachPin(pwmPin, pwmChannel);

		// Create the selected output voltage
		ledcWrite(pwmChannel, 2); // 50%

		/*
		ledc_mode_t speed_mode = LEDC_LOW_SPEED_MODE;
		// LEDC_SPEED_MODE_MAX; 
		//LEDC_LOW_SPEED_MODE; 
		//LEDC_HIGH_SPEED_MODE;

		ledc_timer_t timer_num = LEDC_TIMER_0;
		ledc_timer_bit_t resolution = LEDC_TIMER_10_BIT;
		//LEDC_TIMER_8_BIT;
		// LEDC_TIMER_14_BIT
		ledc_channel_t pwm_channel = LEDC_CHANNEL_0;
		uint32_t frequency = 32768;
		uint32_t duty = 4;
		uint32_t out_pin = 25;
		uint32_t phase = 0;

		ledc_timer_config_t timer_config; 
		timer_config.speed_mode = speed_mode;       // timer mode
		timer_config.duty_resolution = resolution;  // resolution of PWM duty, e.g. LEDC_TIMER_10_BIT
		timer_config.timer_num = timer_num;         // timer index
		timer_config.freq_hz = frequency;           // frequency of PWM signal

		ledc_channel_config_t channel_config = {
			.gpio_num   = 7,
			.speed_mode = speed_mode,
			.channel    = pwm_channel,
			.intr_type  = LEDC_INTR_DISABLE,
			.timer_sel  = timer_num,
			.duty       = duty,
			.hpoint     = phase
		};

		ledc_timer_config(&timer_config);
		ledc_channel_config(&channel_config);
		*/

	}

	void PWM_CRYSTAL::Stop()
	{
		int pwmChannel = 0; // Selects channel 0
		ledcWrite(pwmChannel, 0); // 50%
	}
	