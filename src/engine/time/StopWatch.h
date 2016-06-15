#pragma once
#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class StopWatch
{
public:
	StopWatch();

	sf::Time getElapsedTime() const;

	bool isRunning() const;

	void start();
	void stop();
	void reset();
	void restart();

private:
	sf::Clock m_clock;
	sf::Time m_timeBuffer;
	bool m_running;
};

#endif