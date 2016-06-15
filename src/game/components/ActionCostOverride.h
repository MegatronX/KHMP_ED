#pragma once
#ifndef _ACTIONCOSTOVERRIDE_H_
#define _ACTIONCOSTOVERRIDE_H_

#include <component/Component.h>
#include <actions/Action.h>
#include <utility/Priority.h>
namespace KHMP
{
	class ActionCostOverride : public Component, public Priority
	{
	public:
		const static ComponentType m_componentType = 0x19f1d849;
		ActionCostOverride(Entity* owner, ComponentID id, const int priority = 0) : Component(owner, m_componentType, id), Priority(priority)
		{

		}

		void calculateCost(Action& act, Entity& target, int& mp, int& sp, int& hp)
		{
			mp += act.getMPCost();
			sp += act.getSPCost();
			hp += act.getHPCost();
		}
	protected:
	private:
	};
}

#endif