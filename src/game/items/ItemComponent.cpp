#include "ItemComponent.h"
namespace KHMP
{
	const ComponentType ItemComponent::m_componentType = 0xc94d24f7;// , 0xf8c4, 0x4341, 0x95, 0xc8, 0x3c, 0x65, 0x58, 0xa3, 0x3b, 0x61);


	ItemComponent::ItemComponent(Entity* owner, const ComponentID id) : Component(owner, this->m_componentType, id)
	{

	}
	ItemComponent::~ItemComponent()
	{

	}
	//const ComponentType EquippableComponent::m_componentType = 0xa0a46011;// , 0x4324, 0x4a4e, 0xb6, 0xfe, 0x8d, 0x26, 0xb4, 0x50, 0x9d, 0xf6);

	EquippableComponent::EquippableComponent(Entity* owner, const ComponentID id) : Component(owner, this->m_componentType, id)
	{

	}
	EquippableComponent::~EquippableComponent()
	{

	}
	EquippableComponent::RawClonePtr EquippableComponent::rawClone() const
	{
		return RawClonePtr(new EquippableComponent(*this));
	}

	/*MultiEquippableComponent::MultiEquippableComponent(Entity* owner, const ComponentID id) : EquippableComponent(owner, id)
	{

	}

	MultiEquippableComponent::~MultiEquippableComponent()
	{

	}

	MultiEquippableComponent::MultiEquippableComponent(const MultiEquippableComponent& ref) : EquippableComponent(ref)
	{
		for (auto cmp = ref.m_equippableComponents.begin(); cmp != ref.m_equippableComponents.end(); ++cmp)
		{
			m_equippableComponents[cmp->first] = boost::dynamic_pointer_cast<EquippableComponent>(cmp->second->clone());
			//cmp->second->equip(target);
		}
	}

	MultiEquippableComponent::RawClonePtr MultiEquippableComponent::rawClone() const
	{
		return RawClonePtr(new MultiEquippableComponent(*this));
	}

	int MultiEquippableComponent::equip(Entity& target)
	{
		int result = 0;
		for (auto cmp = m_equippableComponents.begin(); cmp != m_equippableComponents.end(); ++cmp)
		{
			result += cmp->second->equip(target);
		}
		return result;
	}
	int MultiEquippableComponent::unEquip(Entity& target)
	{
		int result = 0;
		for (auto cmp = m_equippableComponents.begin(); cmp != m_equippableComponents.end(); ++cmp)
		{
			result += cmp->second->unEquip(target);
		}
		return result;
	}

	bool MultiEquippableComponent::addEquippableComponent(boost::shared_ptr<EquippableComponent> eqp, const bool replaceExisting)
	{
		return addEquippableComponent(eqp, false, false, replaceExisting);
	}
	bool MultiEquippableComponent::addEquippableComponent(boost::shared_ptr<EquippableComponent> eqp, const bool initCmp, const bool postInitCmp, const bool replaceExisting)
	{
		auto it = m_equippableComponents.find(eqp->getID());
		if (it != m_equippableComponents.end())
		{
			if (!replaceExisting)
			{
				return false;
			}
			it->second->destroy();
		}
		m_equippableComponents[eqp->getID()] = eqp;
		eqp->setOwner(this->m_owner);
		if (initCmp)
			eqp->init();
		if (postInitCmp)
			eqp->postInit();
		return true;
	}
	bool MultiEquippableComponent::removeEquippableComponent(boost::shared_ptr<EquippableComponent> eqp, const bool destroyIfRemoved)
	{
		return eqp.get() != nullptr && removeEquippableComponent(eqp->getID(), destroyIfRemoved);
	}
	bool MultiEquippableComponent::removeEquippableComponent(ComponentID id, const bool destroyIfRemoved)
	{
		auto it = m_equippableComponents.find(id);
		if (it != m_equippableComponents.end())
		{
			if (destroyIfRemoved)
				it->second->destroy();
			m_equippableComponents.erase(it);
			return true;
		}
		return false;
	}
	boost::shared_ptr<EquippableComponent> MultiEquippableComponent::getEquippableComponent(ComponentID id)
	{
		auto it = m_equippableComponents.find(id);
		return it == m_equippableComponents.end() ? boost::shared_ptr<EquippableComponent>() : it->second;
	}

	MultiEquippableComponent& MultiEquippableComponent::operator=(const MultiEquippableComponent& ref)
	{
		if ((*this) == ref)
			return *this;
		EquippableComponent::operator=(ref);
		for (auto cmp = ref.m_equippableComponents.begin(); cmp != ref.m_equippableComponents.end(); ++cmp)
		{
			m_equippableComponents[cmp->first] = boost::dynamic_pointer_cast<EquippableComponent>(cmp->second->clone());
			//cmp->second->equip(target);
		}
		return *this;
	}*/
}
