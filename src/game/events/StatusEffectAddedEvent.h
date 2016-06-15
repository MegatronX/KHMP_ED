#pragma once
#ifndef _STATUSEFFECTADDEDEVENT_H_
#define _STATUSEFFECTADDEDEVENT_H_

#include <events/IEvent.h>
#include <entity/Entity.h>
class Entity;
namespace KHMP
{
	
	class StatusEffectAddedEvent : public IEvent
	{
	public:
		const static EventType m_eventSignature = 0x819ae153;

		StatusEffectAddedEvent(entity_ptr se, Entity* target, sf::Time time = sf::Time::Zero);

		entity_ptr getStatusEffect();
		Entity* getTarget();

		RawClonePtr rawClone() const override;
	protected:
	private:
		entity_ptr m_se;
		Entity* m_target;
	};
}

#endif