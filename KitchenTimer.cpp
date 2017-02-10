#include "KitchenTimer.h"

	uint32_t KitchenTimer::getTime()
	{
		if(isStarted() && CurrentMode == TIMER_MODE_STOPWATCH)
			return (millis() - StartedAt) / 1000;
		
		// If the timer has finished, the return sentence will underflow
		if(CurrentMode == TIMER_MODE_COUNTDOWN)
		{
			if(!isStarted() || hasFinished())
				return Time / 1000;

			return (StartedAt + Time - millis()) / 1000;
		}

		return 0;
	}

	bool KitchenTimer::isStarted()
	{ return Started; }

	void KitchenTimer::start()
	{
		StartedAt = millis();
		Started = true;
	}

	void KitchenTimer::stop()
	{
		Started = false;
		StartedAt = 0;
	}

	void KitchenTimer::toggle()
	{
		if(isStarted())
			stop();
		else
			start();
	}

	uint16_t KitchenTimer::getHours()
	{ return floor(getTime() / 3600); }

	uint8_t KitchenTimer::getMinutes()
	{ return floor(getTime() % 3600 / 60); }

	uint8_t KitchenTimer::getSeconds()
	{ return floor(getTime() % 60); // Floor?
	}

	void KitchenTimer::addHours(uint16_t Hours = 1)
	{ addSeconds(Hours * 3600); }

	void KitchenTimer::addMinutes(uint32_t Minutes = 1)
	{ addSeconds(Minutes * 60); }

	void KitchenTimer::addSeconds(uint32_t Seconds = 1)
	{
		Seconds *= 1000;

		// Prevent buffer overflow
		if(Time > 0 && Seconds > 0xFFFFFFFF - Time)
			return;

		Time += Seconds;

		// If the user added some time, we can think that he wants a countdown!
		CurrentMode = TIMER_MODE_COUNTDOWN;
	}

	void KitchenTimer::reset()
	{
		stop();

		Time = 0;

		// If the user adds time, this ill be changed, else, it will count up
		CurrentMode = TIMER_MODE_STOPWATCH;
	}

	bool KitchenTimer::hasFinished()
	{
		if(isStarted() && CurrentMode == TIMER_MODE_COUNTDOWN)
			return millis() >= StartedAt + Time;

		return false;
	}