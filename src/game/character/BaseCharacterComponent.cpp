#include <character/BaseCharacterComponent.h>

namespace KHMP
{
	BaseCharacterComponent::BaseCharacterComponent(Entity* owner, ComponentID id) : Component(owner, m_componentType, id)
	{

	}
}