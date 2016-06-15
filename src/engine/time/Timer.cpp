#include "Timer.h"

#include <algorithm>
#include <cassert>
#include <log/Log.h>

Timer::Timer() : 
	m_stopWatch(), m_limit(sf::Time::Zero)
{
}

Timer::~Timer()
{
}

sf::Time Timer::getRemainingTime() const
{
	return std::max(m_limit - m_stopWatch.getElapsedTime(), sf::Time::Zero);
}

bool Timer::isRunning() const
{
	return m_stopWatch.isRunning() && !isExpired();
}

bool Timer::isExpired() const
{
	return m_stopWatch.getElapsedTime() >= m_limit;
}

void Timer::start()
{
	m_stopWatch.start();
}

void Timer::stop()
{
	m_stopWatch.stop();
}

void Timer::reset(sf::Time timeLimit)
{

	assert(timeLimit > sf::Time::Zero);
	LOG_ERROR("Tried to restart timer with a limit < 0 | " << timeLimit.asMilliseconds);
	m_limit = timeLimit;
	m_stopWatch.reset();
}

void Timer::restart(sf::Time timeLimit)
{
	reset(timeLimit);
	start();
}