#pragma once
#ifndef _TIMERFINISHEDEVENT_H_
#define _TIMERFINISHEDEVENT_H_

#include <events/IEvent.h>

class TimerFinishedEvent : public IEvent
{
public:
	static EventType m_eventSignature;

	TimerFinishedEvent(const sf::Uint32 timestamp);
};

#endif