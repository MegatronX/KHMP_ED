#include "IEvent.h"

IEvent::IEvent(const EventType eventType, const sf::Time timeStamp)
: m_eventType(eventType), m_timeStamp(timeStamp)
{

}
IEvent::~IEvent()
{

}

const EventType& IEvent::getEventType() const
{
	return m_eventType;
}
sf::Time IEvent::getTimeStamp() const
{
	return m_timeStamp;
}

void IEvent::setTimeStamp(const sf::Time& timeStamp)
{
	m_timeStamp = timeStamp;
}

IEvent::RawClonePtr IEvent::rawClone() const
{
	return new IEvent(*this);
}


void IEvent::setEventType(const EventType& eventType)
{
	m_eventType = eventType;
}

bool IEvent::operator==(const IEvent& refEvt) const
{
	return this->m_timeStamp == refEvt.m_timeStamp &&
		this->m_eventType == refEvt.m_eventType;
}
bool IEvent::operator!=(const IEvent& refEvt) const
{
	return !(*this == refEvt);
}