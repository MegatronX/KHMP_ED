#pragma once
#ifndef _IEVENTMANAGER_H_
#define _IEVENTMANAGER_H_

#include <delegates/FastDelegate.h>
#include <delegates/FastDelegateBind.h>
#include <events/IEvent.h>

typedef fastdelegate::FastDelegate1<ev_ptr, bool> EventListener;

const sf::Time InfiniteEventTime = sf::milliseconds(0xFFFFFFFF);

enum EventAbortType
{
	MostRecent,
	LeastRecent,
	All
};
class Engine;
class IEventManager
{
public:
	IEventManager(Engine* engine, const std::string& name, bool setAsGlobal) : m_engine(engine), m_managerName(name), m_global(setAsGlobal)
	{
	}

	virtual ~IEventManager()
	{
	}

	virtual bool addListener(const EventListener& eventHandler, const EventType& type, bool replaceExisting = false) = 0;

	virtual bool removeListener(const EventListener& eventHandler, const EventType& type) = 0;

	virtual bool triggerEvent(const ev_ptr& eventData) = 0;

	virtual bool queueEvent(const ev_ptr& eventData) = 0;

	virtual bool queueDelayedEvent(const ev_ptr, const sf::Time queueDelay) = 0;

	virtual bool abortQueueEvent(const EventType& evType, const EventAbortType = All) = 0;

	virtual bool abortDeferredQueueEvent(const EventType& evType, const EventAbortType = All) = 0;

	virtual bool tick(sf::Time maxms = InfiniteEventTime) = 0;

	/*static IEventManager* getManager()
	{
		return m_globalManager;
	}
	static void setManager(IEventManager* evmng)
	{
		m_globalManager = evmng;
	}*/
protected:
	Engine* m_engine;
private:
	static IEventManager* m_globalManager;
	std::string m_managerName;
	bool m_global;

};

#endif