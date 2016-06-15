#include "StopWatch.h"

StopWatch::StopWatch()
	: m_clock(), m_timeBuffer(sf::Time::Zero), m_running(false)
{
}

sf::Time StopWatch::getElapsedTime() const
{
	if (m_running)
		return m_timeBuffer + m_clock.getElapsedTime();
	else
		return m_timeBuffer;
}

bool StopWatch::isRunning() const
{
	return m_running;
}

void StopWatch::start()
{
	if (!m_running)
	{
		m_running = true;
		m_clock.restart();
	}
}

void StopWatch::stop()
{
	if (m_running)
	{
		m_running = false;
		m_timeBuffer += m_clock.getElapsedTime();
	}
}

void StopWatch::reset()
{
	m_timeBuffer = sf::Time::Zero;
	m_running = false;
}

void StopWatch::restart()
{
	reset();
	start();
}