#ifndef KitchenTimer_h
#define KitchenTimer_h
 
	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif

	// 99 hours, 59 minutes, 59 seconds
	#define KITCHENTIMER_TIMELIMIT 359999000

	class KitchenTimer
	{
		private:
			// Bit 1 stores Started, and bit 0 CurrentMode
			byte Status = (false << 1) | (TIMER_MODE_STOPWATCH);

			uint32_t StartedAt = 0;
			uint32_t Time = 0;

			void setCurrentMode(uint8_t Mode);
		public:
			static const uint8_t TIMER_MODE_STOPWATCH = 0;
			static const uint8_t TIMER_MODE_COUNTDOWN = 1;

			uint8_t getCurrentMode();

			bool isStarted();

			void start();
			void stop();
			void toggle();

			uint32_t getTime();

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