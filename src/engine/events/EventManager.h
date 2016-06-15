#pragma once
#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include <vector>
#include <deque>
#include <string>
#include <boost/unordered_map.hpp>
#include "IEventManager.h"

#define MAX_EVENT_QUEUES 2

typedef std::vector<EventListener> EventListenerList;
typedef boost::unordered_map<EventType, EventListenerList> EventListenerSets;
typedef std::deque<ev_ptr> EventQueue;
typedef std::deque<std::pair<sf::Time, ev_ptr>> DelayedEventQueue;

class EventManager : public IEventManager
{
public:
	EventManager(Engine* engine, const std::string& mngName, const bool setGlobal);

	virtual ~EventManager();

	virtual bool addListener(const EventListener& eventHandler, const EventType& type, bool replaceExisting = false) override;

	virtual bool removeListener(const EventListener& eventHandler, const EventType& type) override;

	virtual bool triggerEvent(const ev_ptr& eventData) override;

	virtual bool queueEvent(const ev_ptr& eventData) override;

	virtual bool queueDelayedEvent(const ev_ptr, const sf::Time queueDelay);

	virtual bool abortQueueEvent(const EventType& evType, const EventAbortType = All) override;

	virtual bool abortDeferredQueueEvent(const EventType& evType, const EventAbortType = All) override;

	virtual bool tick(sf::Time maxms = InfiniteEventTime) override;
protected:
private:
	EventQueue m_eventQueues[MAX_EVENT_QUEUES];
	DelayedEventQueue m_delayedEventQueue[MAX_EVENT_QUEUES];
	unsigned int m_eventQueueIndex;
	EventListenerSets m_eventListeners;
};

#endif