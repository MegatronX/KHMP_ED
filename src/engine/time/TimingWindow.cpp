#include <time/TimingWindow.h>
#include <log/Log.h>

TimingWindow::TimingWindow() : m_windowStartTime(sf::Time::Zero), m_windowEndTime(sf::Time::Zero), m_windowLength(sf::Time::Zero)
{

}

TimingWindow::TimingWindow(const sf::Time& windowStartTime, const sf::Time windowEndTime) :
m_windowStartTime(windowStartTime), m_windowEndTime(windowEndTime), m_windowLength(windowEndTime - windowStartTime)
{
	if (windowStartTime > windowEndTime)
	{
		LOG_ERROR("Tried to initialize timing window with negative length start time " << windowStartTime << " end time " << windowEndTime);
	}
}

bool TimingWindow::isInWindow(const sf::Time time)
{
	return time >= m_windowStartTime && time <= m_windowEndTime;
}
sf::Time TimingWindow::getWindowDuration() const
{
	return m_windowLength;
}
sf::Time TimingWindow::getWindowStartTime() const
{
	return m_windowStartTime;
}
sf::Time TimingWindow::getWindowEndTime() const
{
	return m_windowEndTime;
}

void TimingWindow::setWindowDuration(const sf::Time& duration)
{
	m_windowEndTime = m_windowStartTime + duration;
	m_windowLength = duration;
}
void TimingWindow::setWindowStartTime(const sf::Time& startTime)
{
	m_windowStartTime = startTime;
	m_windowEndTime = m_windowStartTime + m_windowLength;
}
void TimingWindow::setWindowEndTime(const sf::Time& endTime)
{
	m_windowStartTime = endTime - m_windowLength;
	m_windowEndTime = endTime;
}

void TimingWindow::setWindow(const sf::Time& startTime, const sf::Time& endTime)
{
	m_windowStartTime = startTime;
	m_windowEndTime = endTime;
	m_windowLength = m_windowEndTime - m_windowStartTime;
}
