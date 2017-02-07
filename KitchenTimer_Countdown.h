#ifndef KitchenTimer_Countdown_h
#define KitchenTimer_Countdown_h
 
	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
		#include "pins_arduino.h"
		#include "WConstants.h"
	#endif

	class KitchenTimer_Countdown
	{
		private:
			bool Started = false;
			
			uint32_t StartedAt = 0;
			uint32_t Time;
		public:
			KitchenTimer_Countdown(uint32_t Time = 0)
			: Time(Time * 1000)
			{}

			uint32_t getTime();
			uint32_t getRemainingTime();

			uint16_t getRemainingHours();
			uint8_t getRemainingMinutes();
			uint8_t getRemainingSeconds();
			
			uint32_t addTime(uint32_t T);
			void reset();

			bool isStarted();

			bool start();
			void stop();
			void toggle();

			bool hasFinished();
	};
#endif