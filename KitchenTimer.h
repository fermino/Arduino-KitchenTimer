#ifndef KitchenTimer_h
#define KitchenTimer_h
 
	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
		#include "pins_arduino.h"
		#include "WConstants.h"
	#endif

	class KitchenTimer
	{
		public:
			static const uint8_t TIMER_MODE_STOPWATCH = 0;
			static const uint8_t TIMER_MODE_COUNTDOWN = 1;

			uint8_t CurrentMode = TIMER_MODE_STOPWATCH;

			bool Started = false;
			uint32_t StartedAt = 0;
			uint32_t Time = 0;

			uint32_t getTime();
		public:
			bool isStarted();

			void start();
			void stop();
			void toggle();

			uint16_t getHours();
			uint8_t getMinutes();
			uint8_t getSeconds();

			void addHours(uint16_t Hours = 1);
			void addMinutes(uint32_t Minutes = 1);
			void addSeconds(uint32_t Seconds = 1);

			void reset();

			bool hasFinished();
	};
#endif