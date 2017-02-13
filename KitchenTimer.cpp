#include "KitchenTimer.h"

	uint8_t KitchenTimer::getCurrentMode()
	{ return Status & _BV(0); }

	void KitchenTimer::setCurrentMode(uint8_t Mode)
	{ Status ^= (-Mode ^ Status) & _BV(0); }

	bool KitchenTimer::isStarted()
	{ return Status & 0b10; }

	void KitchenTimer::start()
	{
		StartedAt = millis() - (getCurrentMode() == TIMER_MODE_STOPWATCH ? Time : 0);

		Status |= _BV(1);
	}

	void KitchenTimer::stop()
	{
		Status &= ~_BV(1);

		StartedAt = 0;
	}

	void KitchenTimer::toggle()
	{
		if(isStarted())
			stop();
		else
			start();
	}

	uint32_t KitchenTimer::getTime()
	{
		if(getCurrentMode() == TIMER_MODE_STOPWATCH)
		{
			if(isStarted())
			{
				Time = millis() - StartedAt;

				if(Time >= KITCHENTIMER_TIMELIMIT)
					Time = KITCHENTIMER_TIMELIMIT;
			}

			return Time / 1000;
		}
		
		// If the timer has finished, the return sentence will underflow
		if(getCurrentMode() == TIMER_MODE_COUNTDOWN)
		{
			if(!isStarted() || hasFinished())
				return Time / 1000;

			return (StartedAt + Time - millis()) / 1000;
		}

		return 0;
	}

	uint16_t KitchenTimer::getHours()
	{ return floor(getTime() / 3600); }

	uint8_t KitchenTimer::getMinutes()
	{ return floor(getTime() % 3600 / 60); }

	uint8_t KitchenTimer::getSeconds()
	{ return getTime() % 60; }

	void KitchenTimer::addHours(uint16_t Hours /* = 1 */)
	{ addSeconds(Hours * 3600); }

	void KitchenTimer::addMinutes(uint32_t Minutes /* = 1 */)
	{ addSeconds(Minutes * 60); }

	void KitchenTimer::addSeconds(uint32_t Seconds /* = 1 */)
	{
		Seconds *= 1000;

		// Prevent buffer overflow
		if(Time > 0 && Seconds > 0xFFFFFFFF - Time && Time + Seconds <= KITCHENTIMER_TIMELIMIT)
			return;

		Time += Seconds;

		// If the user added some time, we can think that he wants a countdown!
		setCurrentMode(TIMER_MODE_COUNTDOWN);
	}

	void KitchenTimer::reset()
	{
		stop();

		Time = 0;

		// If the user adds time, this ill be changed, else, it will count up
		setCurrentMode(TIMER_MODE_STOPWATCH);
	}

	bool KitchenTimer::hasFinished()
	{
		if(isStarted() && getCurrentMode() == TIMER_MODE_COUNTDOWN)
			return millis() >= StartedAt + Time;

		return false;
	}