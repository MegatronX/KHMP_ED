#pragma once
#ifndef _TIMEMODULE_H_
#define _TIMEMODULE_H_

#include <sfml/System.hpp>

class TimeModule
{
public:
	TimeModule() : m_timeBuffer(sf::Time::Zero), m_timeSpeed(0.f), m_paused(false)
	{
		m_primaryClock.restart();
		m_secondaryClock.restart();
	}
	sf::Time getGameTime() const
	{
		return m_primaryClock.getElapsedTime() + m_timeBuffer;

	}
	sf::Time getRealTime() const
	{
		return m_primaryClock.getElapsedTime();
	}
protected:
private:
	sf::Time m_timeBuffer;
	float m_timeSpeed;
	bool m_paused;
	sf::Clock m_primaryClock;
	sf::Clock m_secondaryClock;
};

#endif