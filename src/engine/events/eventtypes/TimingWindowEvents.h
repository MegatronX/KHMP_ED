#pragma once
#ifndef _TIMINGWINDOWEVENTS_H_
#define _TIMINGWINDOWEVENTS_H_

#include <events/IEvent.h>
#include <time/TimingWindow.h>

class TimingWindowEvent : public IEvent
{
public:
	const static EventType m_eventSignature = 0x7aca0a67;// , 0xfa33, 0x47b3, 0x89, 0x48, 0x2, 0xf5, 0xb0, 0xe1, 0xe5, 0x23);
	
	TimingWindowEvent(const unsigned int timingWindowID, const bool hit, const bool expired, const bool missed, const TimingWindow& window, const sf::Time timestamp = sf::Time::Zero);
	RawClonePtr rawClone() const override;

	TimingWindow& getWindow();

	bool getWindowHit() const;
	bool getWindowExpired() const;
	bool getWindowMissed() const;

	unsigned int getTimingWindowID() const;
private:
	unsigned int m_timingWindowID;
	TimingWindow m_window;
	bool m_windowHit;
	bool m_windowExpired;
	bool m_windowMissed;
};

#endif