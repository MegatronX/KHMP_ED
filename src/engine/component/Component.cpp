#include "Component.h"

#include <entity/Entity.h>

boost::unordered_map<std::string, ComponentType> ComponentStringTypeToType = boost::unordered_map<std::string, ComponentType>();
boost::unordered_map<ComponentType, std::string> ComponentTypeToTypeString = boost::unordered_map<ComponentType, std::string>();

const std::string Component::m_emptyProperty;

Component::Component(const ComponentType& type, const ComponentID& id) 
	: m_id(id), m_type(type), m_initialized(false), m_destroyed(false)
{

}
Component::Component(Entity* owner, const ComponentType& type, const ComponentID& id) 
: m_owner(owner), m_id(id), m_type(type)
{

}

Component::Component(boost::shared_ptr<Entity> owner, const ComponentType& type, const ComponentID& id)
	: m_owner(owner != nullptr ? owner.get() : nullptr), m_id(id), m_type(type)
{

}

Component::Component(Entity& owner, const ComponentType& type, const ComponentID& id)
	: m_owner(&owner), m_id(id), m_type(type)
{

}

Component::~Component()
{
	if (!m_destroyed)
		destroy();
}

void Component::init()
{
	m_initialized = true;
}
void Component::postInit()
{
}
void Component::destroy()
{
	m_destroyed = true;
}
const Entity* Component::getOwner() const
{
	return m_owner;
}
bool Component::ownedBy(const Entity* ent) const
{
	return m_owner != nullptr && ent != nullptr && (*m_owner == *ent);
}
void  Component::setOwner(Entity* owner)
{
	m_owner = owner;
}

bool Component::addProperty(const std::string& key, const std::string& value, bool overwriteExisting)
{
	auto it = m_properties.find(key);
	if (it != m_properties.end() && !overwriteExisting)
		return false;
	m_properties[key] = value;
	return true;
}

bool Component::removeProperty(const std::string& key)
{
	auto it = m_properties.find(key);
	if (it == m_properties.end())
		return false;
	m_properties.erase(it);
	return true;
}

bool Component::hasProperty(const std::string& key)
{
	return m_properties.find(key) != m_properties.end();
}

const std::string& Component::getProperty(const std::string& key)
{
	auto it = m_properties.find(key);
	if (it != m_properties.end())
		return it->second;
	return m_emptyProperty;
}

bool Component::hasFlag(const std::string& flag) const
{
	return m_flags.find(flag) != m_flags.end();
}
bool Component::addFlag(const std::string& flag)
{
	m_flags.insert(flag);
	return true;
}
bool Component::removeFlag(const std::string& flag)
{
	auto fl = m_flags.find(flag);
	if (fl != m_flags.end())
	{
		m_flags.erase(flag);
		return true;
	}
	return false;
}

bool Component::hasComponent(const ComponentType type) const
{
	return m_subComponents.find(type) != m_subComponents.end();
}

bool Component::addComponent(boost::shared_ptr<Component> component, const bool initComponent, const bool postInitComponent, const bool overwriteExisting)
{
	bool added = false;
	auto it = m_subComponents.find(component->getType());
	if (it == m_subComponents.end() || overwriteExisting)
	{
		//it->second->destroy();
		it->second = component;
		component->setOwner(m_owner);
		if (initComponent)
			component->init();
		if (postInitComponent)
			component->postInit();
	}
	return added;
}

bool Component::removeComponent(const ComponentType type, const ComponentID id, bool destroyComponent)
{
	auto it = m_subComponents.find(type);
	if (it != m_subComponents.end())
	{
		if (destroyComponent)
			it->second->destroy();
		m_subComponents.erase(it);
		return true;
	}
	return false;
}

bool Component::operator==(const Component& cmp) const
{
	return cmp.getID() == getID() && (cmp.m_owner != nullptr && m_owner != nullptr && (*cmp.m_owner) == (*m_owner));
}
bool Component::operator!=(const Component& cmp) const
{
	return !(cmp == *this);
}
//IMPLEMENT CORRECTLY
/*Component& Component::operator=(const Component& cmp)
{
	return *this;
}*/
 

