#include "EventManager.h"
#include <Engine.h>
#include <log/Log.h>
#include <events/eventtypes/InputActionEvent.h>

EventManager::EventManager(Engine* engine, const std::string& mngName, const bool setGlobal)
: IEventManager(engine, mngName, setGlobal), m_eventQueueIndex(0)
{
}

EventManager::~EventManager()
{
}

bool EventManager::addListener(const EventListener& eventHandler, const EventType& type, bool replaceExisting)
{
	auto& eventSet = m_eventListeners[type];
	for (auto ev = eventSet.begin(); ev != eventSet.end(); ++ev)
	{
		if (*ev == eventHandler)
		{
			if (!replaceExisting)
			{
				return false;
			}
			else
			{
				eventSet.erase(ev);
			}
		}
	}

	eventSet.push_back(eventHandler);
	return true;
}

bool EventManager::removeListener(const EventListener& eventHandler, const EventType& type)
{
	bool removed = false;
	auto it = m_eventListeners.find(type);
	if (it != m_eventListeners.end())
	{
		auto& eventSet = it->second;
		int preCheck = eventSet.size();
		for (auto event = eventSet.begin(); event != eventSet.end(); ++event)
		{
			if ((*event) == eventHandler)
			{
				eventSet.erase(event);
				removed = true;
				break;
			}
		}
		int eventSetSize = eventSet.size();
	}
	return removed;
}

bool EventManager::triggerEvent(const ev_ptr& event)
{
	bool triggered = false;
	auto eventSet = m_eventListeners.find(event->getEventType());
	if (event->getEventType() == InputActionEvent::m_eventSignature)
	{
		int stop = 0;
	}
	if (eventSet != m_eventListeners.end())
	{
		int eventSetSize = eventSet->second.size();
		for (auto eventhandler = eventSet->second.begin(); eventhandler != eventSet->second.end(); ++eventhandler)
		{
			if (event->getTimeStamp() == sf::Time::Zero)
			{
				auto ptrcp = event;
				ptrcp->setTimeStamp(m_engine->getRealTime());
				(*eventhandler)(ptrcp);
			}
			else
			{
				(*eventhandler)(event);
			}
			triggered = true;
		}
	}
	return triggered;
}

bool EventManager::queueEvent(const ev_ptr& eventData)
{
	auto eventSet = m_eventListeners.find(eventData->getEventType());
	if (eventSet != m_eventListeners.end())
	{
		m_eventQueues[m_eventQueueIndex].push_back(eventData);
		if (m_eventQueues[m_eventQueueIndex].back()->getTimeStamp() == sf::Time::Zero)
		{
			m_eventQueues[m_eventQueueIndex].back()->setTimeStamp(m_engine->getRealTime());
		}
		return true;
	}
	return false;
}

bool EventManager::queueDelayedEvent(const ev_ptr event, const sf::Time queueDelay)
{
	bool inserted = false;
	sf::Time time = m_engine->getRealTime();
	sf::Time triggerTime =  time + queueDelay;
	if (m_delayedEventQueue[m_eventQueueIndex].size() == 0 || m_delayedEventQueue[m_eventQueueIndex].back().first < triggerTime)
	{
		m_delayedEventQueue[m_eventQueueIndex].push_back(std::pair<sf::Time, ev_ptr>(triggerTime, event));
		inserted = true;
	}
	else if (m_delayedEventQueue[m_eventQueueIndex].front().first > triggerTime)
	{
		m_delayedEventQueue[m_eventQueueIndex].push_front(std::pair<sf::Time, ev_ptr>(triggerTime, event));
		inserted = true;
	}
	else
	{
		for (auto ev = m_delayedEventQueue[m_eventQueueIndex].begin(); ev != m_delayedEventQueue[m_eventQueueIndex].end(); ++ev)
		{
			if (triggerTime <= ev->first)
			{
				m_delayedEventQueue[m_eventQueueIndex].insert(ev, std::pair<sf::Time, ev_ptr>(triggerTime, event));
				inserted = true;
				break;
			}
		}
		if (!inserted)
		{
			m_delayedEventQueue[m_eventQueueIndex].push_back(std::pair<sf::Time, ev_ptr>(triggerTime, event));
			inserted = true;
		}
	}
	return inserted;
}

bool EventManager::abortQueueEvent(const EventType& evType, const EventAbortType)
{
	return false;
}

bool EventManager::abortDeferredQueueEvent(const EventType& evType, const EventAbortType)
{
	return false;
}

bool EventManager::tick(const sf::Time maxms)
{
	auto time = m_engine->getRealTime();
	auto maxTime = maxms == InfiniteEventTime ? InfiniteEventTime : (time + maxms);

	auto& evQueue = m_eventQueues[m_eventQueueIndex];

	unsigned int i = 0;
	bool checkDelayedQueue = m_delayedEventQueue[m_eventQueueIndex].size() > 0 && m_delayedEventQueue[m_eventQueueIndex].front().first < time;
	for (; evQueue.size() > 0 && time < maxTime; ++i, time = m_engine->getRealTime())
	{
		//std::cout << "Events left: " << evQueue.size() << std::endl;
		auto& event = evQueue[0];
		triggerEvent(event);
		evQueue.pop_front();
		while (checkDelayedQueue)
		{
			triggerEvent(m_delayedEventQueue[m_eventQueueIndex].front().second);
			m_delayedEventQueue[m_eventQueueIndex].pop_front();
			checkDelayedQueue = m_delayedEventQueue[m_eventQueueIndex].size() > 0 && m_delayedEventQueue[m_eventQueueIndex].front().first < time;
		}
	}
#ifdef DEBUG
	if (evQueue.size() > 0)
	{
		LOG_DEBUG("Ran out of time while processing events.");
	}
#endif
	while (checkDelayedQueue)
	{
		triggerEvent(m_delayedEventQueue[m_eventQueueIndex].front().second);
		m_delayedEventQueue[m_eventQueueIndex].pop_front();
		checkDelayedQueue = m_delayedEventQueue[m_eventQueueIndex].size() > 0 && m_delayedEventQueue[m_eventQueueIndex].front().first < time;
	}
	return true;
}