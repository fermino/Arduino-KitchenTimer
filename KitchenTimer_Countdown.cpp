#include "KitchenTimer_Countdown.h"

	// Time limit control

	uint32_t KitchenTimer_Countdown::getTime()
	{ return Time; }

	uint32_t KitchenTimer_Countdown::getRemainingTime()
	{
		if(!Started)
			return Time;

		// If we don't test this, the next return sentence could underflow
		if(hasFinished())
			return 0;

		return (StartedAt + Time - millis()) / 1000;
	}

	uint16_t KitchenTimer_Countdown::getRemainingHours()
	{
		return floor(getRemainingTime() / 3600);
	}

	uint8_t KitchenTimer_Countdown::getRemainingMinutes()
	{
		return floor(getRemainingTime() % 3600 / 60);
	}

	uint8_t KitchenTimer_Countdown::getRemainingSeconds()
	{
		return floor(getRemainingTime() % 60);
	}

	uint32_t KitchenTimer_Countdown::addTime(uint32_t T)
	{
		T *= 1000;

		// If what I want to add is more than what I CAN add, the addition will overflow
		if(Time > 0 && T > 0xFFFFFFFF - Time) 
			return;

		Time += T;

		return Time;
	}

	void KitchenTimer_Countdown::reset()
	{
		stop();

		Time = 0;
	}

	// Start/Stop

	bool KitchenTimer_Countdown::isStarted()
	{ return Started; }

	bool KitchenTimer_Countdown::start()
	{
		if(Time == 0)
			return false;

		StartedAt = millis();
		Started = true;

		return true;
	}

	void KitchenTimer_Countdown::stop()
	{
		StartedAt = 0;
		Started = false;
	}

	void KitchenTimer_Countdown::toggle()
	{
		if(Started)
			stop();
		else
			start();
	}

	// This function checks if the desired time lapse is finished

	bool KitchenTimer_Countdown::hasFinished()
	{
		return Started && millis() > StartedAt + Time;
	}

	// Add copyright and license info. 
	// Add examples and keywords.txt