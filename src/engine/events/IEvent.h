#pragma once
#ifndef _IEVENTDATA_H_
#define _IEVENTDATA_H_

#include <sfml/System.hpp>
#include <boost/shared_ptr.hpp>
#include <utilities/Cloneable.h>

typedef sf::Uint32 EventType;

class IEvent : public ICloneable<IEvent>
{
public:
	IEvent(const EventType eventType, const sf::Time timeStamp = sf::Time::Zero);
	virtual ~IEvent();

	virtual const EventType& getEventType() const;
	sf::Time getTimeStamp() const;

	void setTimeStamp(const sf::Time& timeStamp);

	RawClonePtr rawClone() const override;

	bool operator==(const IEvent& refEvt) const;
	bool operator!=(const IEvent& refEvt) const;
protected:

	void setEventType(const EventType& eventType);
private:
	sf::Time m_timeStamp;
	EventType m_eventType;
};
typedef boost::shared_ptr<IEvent> ev_ptr;
#endif