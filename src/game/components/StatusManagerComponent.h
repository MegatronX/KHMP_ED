#pragma once
#ifndef _STATUSMANAGERCOMPONENT_H_
#define _STATUSMANAGERCOMPONENT_H_

#include <component/Component.h>
#include <events/IEvent.h>

namespace KHMP
{
	class StatusEffectManager : public Component
	{
	public:
		static const ComponentType m_componentType = 0x3b2945cf;
		StatusEffectManager(Entity* owner, const ComponentID& id);

		bool addStatusEffect(boost::shared_ptr<Entity> se);
	protected:
		virtual bool handleBattleTickEvent(ev_ptr tickEv);
		virtual bool handleStatusEffectRemovalEvent(ev_ptr rmvEv);
		virtual bool handleStatusEffectAplliedEvent(ev_ptr addEv);
		virtual bool validateAsStatusEffect(boost::shared_ptr<Entity> se);

		virtual bool broadcastStatusEffectAddedEvent();
		virtual bool broadcastStatusEffectRemovedEvent();
	private:
		boost::unordered_map<std::string, boost::shared_ptr<Entity> > m_statusEffects;
	};
}

#endif