#include <components/StatusManagerComponent.h>
#include <entity/Entity.h>
#include <components/StatusEffectComponent.h>

#include <events/StatusEffectAddedEvent.h>

namespace KHMP
{
	StatusEffectManager::StatusEffectManager(Entity* owner, const ComponentID& id) : Component(owner, m_componentType, id)
	{

	}

	bool StatusEffectManager::addStatusEffect(entity_ptr se)
	{
		bool added = false;
		if (validateAsStatusEffect(se))
		{

		}
		return added;
	}

	bool StatusEffectManager::handleBattleTickEvent(ev_ptr tickEv)
	{
		bool handled = false;
		return handled;
	}
	bool StatusEffectManager::handleStatusEffectRemovalEvent(ev_ptr rmvEv)
	{
		bool handled = false;
		return handled;
	}

	bool StatusEffectManager::handleStatusEffectAplliedEvent(ev_ptr addEv)
	{
		bool handled = false;

		if (addEv->getEventType() == StatusEffectAddedEvent::m_eventSignature)
		{
			auto seAddedEvent = boost::dynamic_pointer_cast<StatusEffectAddedEvent>(addEv);
			if (seAddedEvent && (*seAddedEvent->getTarget()) == (*this->getOwner()))
			{
				addStatusEffect(seAddedEvent->getStatusEffect());
				handled = true;
			}
		}

		return handled;
	}

	bool StatusEffectManager::broadcastStatusEffectAddedEvent()
	{
		bool handled = false;
		return handled;
	}
	bool StatusEffectManager::broadcastStatusEffectRemovedEvent()
	{
		bool handled = false;
		return handled;
	}

	bool StatusEffectManager::validateAsStatusEffect(entity_ptr se)
	{
		return se && se->getComponents(StatusEffectComponent::m_componentType).size() > 0;
	}
}