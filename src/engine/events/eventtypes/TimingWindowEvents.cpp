#include <events/eventtypes/TimingWindowEvents.h>

TimingWindowEvent::TimingWindowEvent(const unsigned int timingWindowID, const bool hit, const bool expired, const bool missed, const TimingWindow& window, const sf::Time timestamp)
	: m_timingWindowID(timingWindowID), m_windowHit(hit), m_windowExpired(expired), m_windowMissed(missed), m_window(window), IEvent(m_eventSignature, timestamp)
{

}
TimingWindowEvent::RawClonePtr TimingWindowEvent::rawClone() const
{
	return RawClonePtr(new TimingWindowEvent(*this));
}

TimingWindow& TimingWindowEvent::getWindow()
{
	return m_window;
}

bool TimingWindowEvent::getWindowHit() const
{
	return m_windowHit;
}

bool TimingWindowEvent::getWindowExpired() const
{
	return m_windowExpired;
}

bool TimingWindowEvent::getWindowMissed() const
{
	return m_windowMissed;
}

unsigned int TimingWindowEvent::getTimingWindowID() const
{
	return m_timingWindowID; 
}