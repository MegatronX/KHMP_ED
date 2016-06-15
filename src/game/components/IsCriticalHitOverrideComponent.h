#pragma once
#ifndef _ISCRITHITOVERRIDECOMPONENT_H_
#define _ISCRITHITOVERRIDECOMPONENT_H_

#include <component/Component.h>
#include <utility/Priority.h>
namespace KHMP
{
	class BattleField;
	class IsCriticalHitOverrideComponent : public Component, public Priority
	{
	public:
		static const ComponentType m_componentType = 0x735b3005;
		IsCriticalHitOverrideComponent(Entity* owner, ComponentID id, const int priority = 0) : Component(owner, m_componentType, id),
			Priority(priority)
		{

		}

		virtual bool isCriticalHit(Action& action, Entity& target, BattleField& field, bool alreadyCritical = false)
		{
			return alreadyCritical;
		}

	protected:
	};
}



#endif