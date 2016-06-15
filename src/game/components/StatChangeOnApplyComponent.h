#pragma once
#ifndef _STATCHANGEONAPPLYCOMPONENT_H_
#define _STATCHANGEONAPPLYCOMPONENT_H_

#include <components/ApplyComponent.h>
#include <character/Stats.h>
namespace KHMP
{
	class StatChangeOnApplyComponent : public ApplyComponent
	{
	public:
		StatChangeOnApplyComponent(Entity* owner, ComponentID id, const int priority = 0) : ApplyComponent(owner, id, priority)
		{

		}

		virtual bool Apply(Entity* target, BattleField* field = nullptr) override
		{
			return false;
		}

		virtual void addStatAdder(const Stat stat, const int add)
		{
			m_statAdds[stat] += add;
		}

		virtual void addStatMultiplier(const Stat stat, const float mul)
		{
			m_multipliers[stat] += mul;
		}
	protected:
		boost::unordered_map<Stat, int> m_statAdds;
		boost::unordered_map<Stat, float> m_multipliers;
	};
}


#endif