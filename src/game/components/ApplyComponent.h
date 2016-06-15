#pragma once
#ifndef _APPLYCOMPONENT_H_
#define _APPLYCOMPONENT_H_

#include <component/Component.h>
#include <utility/Priority.h>

namespace KHMP
{
	class BattleField;
	class ApplyComponent : public Component, public Priority
	{
	public:
		const static ComponentType m_componentType = 0xb6ceb46e;
		ApplyComponent(Entity* owner, ComponentID id, const int priority = 0) : Component(owner, m_componentType, id), Priority(priority)
		{

		}

		virtual bool Apply(Entity* target, BattleField* field = nullptr)
		{
			return false;
		}
	};
}
#endif