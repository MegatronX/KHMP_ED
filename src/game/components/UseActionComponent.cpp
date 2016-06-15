#include <components/UseActionComponent.h>

namespace KHMP
{
	UseActionComponent::UseActionComponent(Entity* owner, ComponentID id) : Component(owner, m_componentType, id)
	{

	}

	void UseActionComponent::UseAction(Action& act, BattleField& field, Mechanics& mechanics)
	{

	}

	UseActionAgainstTargetComponent::UseActionAgainstTargetComponent(Entity* owner, ComponentID id)
	{

	}

	void UseActionAgainstTargetComponent::UseActionAgainstTarget(Action& act, Entity& ent, Mechanics& mechanics)
	{

	}
}