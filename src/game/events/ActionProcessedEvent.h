#pragma once
#ifndef _ACTIONPROCESSEDEVENT_H_
#define _ACTIONPROCESSEDEVENT_H_

#include <events/IEvent.h>
#include <actions/Action.h>

namespace KHMP
{
	class BattleField;
	class Mechanics;
	class ActionProcessedEvent : public IEvent
	{
	public:
		const static EventType m_eventSignature = 0x869be153;
		ActionProcessedEvent(Action* action, Entity* target, BattleField* field, Mechanics* mechanics, sf::Time time = sf::Time::Zero);

		//Entity* getOriginalTarget() const;
		Entity* getTarget() const;
		Action* getAction() const;
	protected:
	private:
		Action* m_processedAction;
		//Entity* m_finalTarget;
		Entity* m_originalTarget;
		BattleField* m_field;
		Mechanics* m_mechanics;
	};
}

#endif