#pragma once
#ifndef _TIMINGWINDOW_H_
#define _TIMINGWINDOW_H_

#include <sfml/System/Time.hpp>

class TimingWindow
{
public:
	TimingWindow();
	TimingWindow(const sf::Time& windowStartTime, const sf::Time windowEndTime);

	bool isInWindow(const sf::Time time);
	sf::Time getWindowDuration() const;
	sf::Time getWindowStartTime() const;
	sf::Time getWindowEndTime() const;

	void setWindowDuration(const sf::Time& duration);
	void setWindowStartTime(const sf::Time& statTime);
	void setWindowEndTime(const sf::Time& endTime);

	void setWindow(const sf::Time& startTime, const sf::Time& endTime);
protected:
	
private:
	sf::Time m_windowStartTime;
	sf::Time m_windowEndTime;
	sf::Time m_windowLength;
};

#endif