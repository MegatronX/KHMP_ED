#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include <sfml/System/Time.hpp>
#include <time/StopWatch.h>

class Timer
{
public:
	Timer();
	~Timer();

	sf::Time getRemainingTime() const;
	bool isRunning() const;
	bool isExpired() const;

	void start();
	void stop();

	virtual void reset(sf::Time timeLimit);
	virtual void restart(sf::Time timeLimit);

private:
	StopWatch m_stopWatch;
	sf::Time m_limit;
};

#endif