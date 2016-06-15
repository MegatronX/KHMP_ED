#pragma once
#ifndef _CALCDAMAGEOVERRIDE_H_
#define _CALCDAMAGEOVERRIDE_H_

#include <component/Component.h>
#include <utility/Priority.h>
namespace KHMP
{
	class Action;
	class BattleField;
	class CalcDamageOverrideComponent : public Component, public Priority
	{
	public:
		static const ComponentType m_componentType = 0x449e0791;
		CalcDamageOverrideComponent(Entity* owner, ComponentID id) : Component(owner, m_componentType, id)
		{

		}

		int calculateDamage(Action& act, Entity& target, BattleField& field)
		{
			return 0;
		}
	protected:
	private:

	};
}

#endif