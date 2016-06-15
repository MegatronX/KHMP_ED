#pragma once
#ifndef _TARGETCHANGECOMPONENT_H_
#define _TARGETCHANGECOMPONENT_H_

#include <component/Component.h>

namespace KHMP
{
	class BattleField;
	class TargetChangeComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0xd7d954ca;
		TargetChangeComponent(Entity* owner, ComponentID id) : Component(owner, m_componentType, id)
		{

		}

		virtual bool changeTargetting(Entity& action, Entity& target, BattleField& field) = 0;
	};
}

#endif