#pragma once
#ifndef _ISHITOVERRIDECOMPONENT_H_
#define _ISHITOVERRIDECOMPONENT_H_

#include <component/Component.h>
#include <utility/Priority.h>
namespace KHMP
{
	class BattleField;
	class IsHitOverrideComponent : public Component, public Priority
	{
	public:
		static const ComponentType m_componentType = 0x20ca8e22;
		IsHitOverrideComponent(Entity* owner, ComponentID id, const int priority = 0) : Component(owner, m_componentType, id),
			Priority(priority)
		{

		}

		virtual bool isHit(Action& action, Entity& target, BattleField& field, bool alreadyHit = false)
		{
			return alreadyHit;
		}

	protected:
	};
}

#endif