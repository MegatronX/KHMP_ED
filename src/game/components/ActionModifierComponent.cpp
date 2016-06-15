#include <components/ActionModifierComponent.h>

namespace KHMP
{
	ActionModifierComponent::ActionModifierComponent(Entity* owner, ComponentID id) : Component(owner, id, m_componentType)
	{

	}
	ActionModifierComponent::ActionModifierComponent(Entity* owner, ComponentID id, const boost::unordered_set<CallCondition>& cc) : Component(owner, id, m_componentType),
		m_callConditions(cc)
	{

	}

	void ActionModifierComponent::addCallCondition(const CallCondition cc)
	{
		m_callConditions.insert(cc);
	}
	bool ActionModifierComponent::hasCallCondition(const CallCondition cc) const
	{
		return m_callConditions.find(cc) != m_callConditions.end();
	}

	bool ActionModifierComponent::modifyAction(Action& action, BattleField* field, Mechanics* mechanics)
	{
		return false;
	}
	bool ActionModifierComponent::unmodifyAction(Action& action, BattleField* field, Mechanics* mechanics)
	{
		return false;
	}

	bool ActionModifierComponent::removeCallCondition(const CallCondition cc)
	{
		return  m_callConditions.erase(cc) > 0;
	}
}