#pragma once
#ifndef _ACTIONMODIFIERCOMPONENT_H_
#define _ACTIONMODIFIERCOMPONENT_H_

#include <actions/Action.h>
#include <battle/Mechanics.h>
#include <battle/BattleField.h>
#include <battle/CallConditions.h>

#include <boost/unordered_set.hpp>
#include <utility/Priority.h>
namespace KHMP
{
	class ActionModifierComponent : public Component, public Priority
	{
	public:
		static const ComponentType m_componentType = 0x51d65626;
		ActionModifierComponent(Entity* owner, ComponentID id);
		ActionModifierComponent(Entity* owner, ComponentID id, const boost::unordered_set<CallCondition>& cc);

		void addCallCondition(const CallCondition cc);
		bool hasCallCondition(const CallCondition cc) const;

		bool modifyAction(Action& action, BattleField* field, Mechanics* mechanics);
		bool unmodifyAction(Action& action, BattleField* field, Mechanics* mechanics);
	protected:
		bool removeCallCondition(const CallCondition cc);
	private:
		boost::unordered_set<CallCondition> m_callConditions;
	};
}

#endif