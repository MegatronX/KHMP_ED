#include "Entity.h"


Entity::Entity(const EntityID id) : m_id(id)
{

}
Entity::Entity(const EntityID id, const std::string& entityName) : m_id(id), m_entityName(entityName)
{

}
Entity::Entity(const Entity& ref) : m_entityName(ref.m_entityName), m_id(ref.m_id)
{
	m_entityName = ref.m_entityName;
	m_properties = ref.m_properties;
	for (auto compType = ref.m_components.begin(); compType != ref.m_components.end(); ++compType)
	{
		for (auto cmp = compType->second.begin(); cmp != compType->second.end(); ++cmp)
		{
			m_components[compType->first].push_back((*cmp)->clone());
		}
	}
}
Entity::~Entity()
{
	
}

void Entity::initEntity()
{
	for (auto compType = m_components.begin(); compType != m_components.end(); ++compType)
	{
		for (auto cmp = compType->second.begin(); cmp != compType->second.end(); ++cmp)
		{
			(*cmp)->init();
		}
	}
}
void Entity::destroyEntity()
{
	for (auto compType = m_components.begin(); compType != m_components.end(); ++compType)
	{
		for (auto cmp = compType->second.begin(); cmp != compType->second.end(); ++cmp)
		{
			(*cmp)->destroy();
		}
	}
}
void Entity::postInit()
{
	for (auto compType = m_components.begin(); compType != m_components.end(); ++compType)
	{
		for (auto cmp = compType->second.begin(); cmp != compType->second.end(); ++cmp)
		{
			(*cmp)->postInit();
		}
	}
}

bool Entity::addComponent(boost::shared_ptr<Component> component, const bool overwriteExisting)
{
	if (!overwriteExisting)
	{
		auto it = m_components.find(component->getID());
		if (it != m_components.end())
		{
			return false;
		}
	}
	m_componentsByID[component->getID()] = component.get();
	m_components[component->getType()].push_back(component);
	/*auto cachetest = m_componentsCache.find(component->getType());
	if (cachetest != m_componentsCache.end())
	{
		cachetest->second.first = true;
	}*/
	component->setOwner(this);
	//component->init();
	//m_cacheDirty = true;
	return true;
}

bool Entity::addComponent(Component* component, const bool overwriteExisting)
{
	return addComponent(boost::shared_ptr<Component>(component), overwriteExisting);
}

bool Entity::addComponent(boost::shared_ptr<Component> component, const bool initComponent, const bool postInitComponent, const bool overwriteExisting)
{
	if (addComponent(component, overwriteExisting))
	{
		if (initComponent)
			component->init();
		if (postInitComponent)
			component->postInit();
		return true;
	}
	return false;
}

bool Entity::addComponent(Component* component, const bool initComponent, const bool postInitComponent, const bool overwriteExisting)
{
	return addComponent(boost::shared_ptr<Component>(component), initComponent, postInitComponent, overwriteExisting);
}

bool Entity::addComponentAsOnlyInstanceOfType(boost::shared_ptr<Component> component, const bool initComponent, const bool postInitComponent)
{
	removeComponents(component->getType());
	addComponent(component);
	if (initComponent)
		component->init();
	if (postInitComponent)
		component->postInit();
	return true;
}

bool Entity::hasComponent(const ComponentID id) const
{
	//auto it = m_components.find(id);
	return m_components.find(id) != m_components.end();
}

bool Entity::hasComponents(const ComponentType type) const
{
	return getComponentCount(type) > 0;
}
int Entity::getComponentCount(const ComponentType type) const
{
	auto it = m_components.find(type);
	return it == m_components.end() ? 0 : it->second.size();
}

int Entity::getComponentCount() const
{
	int cmpCount = 0;
	for (auto type = m_components.begin(); type != m_components.end(); ++type)
	{
		cmpCount += type->second.size();
	}
	return cmpCount;
}

/*bool Entity::removeComponent(const ComponentType type, const ComponentID id, bool destroyComponent)
{
	bool removed = false;

}*/
bool Entity::removeComponents(const ComponentType type, bool destroyComponents)
{
	bool removed = false;
	auto it = m_components.find(type);
	if (it != m_components.end())
	{
		for (auto cmp = it->second.begin(); cmp != it->second.end(); ++cmp)
		{
			auto idit = m_componentsByID.find((*cmp)->getID());
			if (idit != m_componentsByID.end())
			{
				m_componentsByID.erase(idit);
			}
			if (destroyComponents)
				(*cmp)->destroy();
			removed = true;

		}

		m_components.erase(it);

	}
	return removed;
}

bool Entity::removeComponent(const ComponentID id, bool destroyComponent)
{
	auto cmpbyid = m_componentsByID.find(id);
	if (cmpbyid != m_componentsByID.end())
	{
		bool foundmatch = false;
		std::vector<boost::shared_ptr<Component> >::iterator cmp;
		for (auto type = m_components.begin(); type != m_components.end(); ++type)
		{
			cmp = type->second.begin();
			for (; cmp != type->second.end(); ++cmp)
			{
				if ((*cmp)->getID() == id)
				{
					foundmatch = true;
					break;
				}
			}
			if (foundmatch)
			{
				type->second.erase(cmp);
				if (type->second.size() == 0)
				{
					m_components.erase(type);
				}
				break;
			}

		}
		if (!foundmatch)
		{
			throw std::exception("ERROR: Attempted to remove a non existant component despite finding the id");
		}
		/*if (destroyComponent)
			cmp->second->destroy();
			*/
		/*auto cachetest = m_componentsCache.find(cmpbyid->second->getType());
		if (cachetest != m_componentsCache.end())
		{
			cachetest->second.first = true;
		}*/
		m_componentsByID.erase(cmpbyid);
		return true;
	}
	return false;
}

bool Entity::removeComponent(const Component* component, bool destroyComponent)
{
	return component != nullptr && removeComponent(*component);
}

bool Entity::removeComponent(const boost::shared_ptr<Component> component, bool destroyComponent)
{
	return removeComponent(component.get());
}

bool Entity::removeComponent(const Component& component, bool destroyComponent)
{
	return removeComponent(component.getID());
}

bool Entity::hasProperty(const std::string& property) const
{
	return m_properties.find(property) != m_properties.end();
}
bool Entity::addProperty(const std::string& property, const std::string& value, const bool overwriteExisting)
{
	if (!overwriteExisting)
	{
		auto it = m_properties.find(property);
		if (it != m_properties.end())
		{
			return false;
		}
	}
	m_properties[property] = value;
	return true;
}
std::string Entity::getProperty(const std::string& property) const
{
	auto it = m_properties.find(property);
	return it != m_properties.end() ? it->second : std::string();
}

bool Entity::removeProperty(const std::string& property)
{
	auto it = m_properties.find(property);
	if (it != m_properties.end())
	{
		m_properties.erase(it);
		return true;
	}
	return false;
}

bool Entity::hasFlag(const std::string& flag) const
{
	return m_flags.find(flag) != m_flags.end();
}
bool Entity::addFlag(const std::string& flag)
{
	m_flags.insert(flag);
	return true;
}
bool Entity::removeFlag(const std::string& flag)
{
	auto fl = m_flags.find(flag);
	if (fl != m_flags.end())
	{
		m_flags.erase(fl);
		return true;
	}
	return false;
}

Entity::RawClonePtr Entity::rawClone() const
{
	return new Entity(*this);
}


const std::string& Entity::getEntityName() const
{
	return m_entityName;
}

void Entity::setEntityName(const std::string& name)
{
	m_entityName = name;
}


bool Entity::operator==(const Entity& cmp) const
{
	return cmp.m_entityName == cmp.m_entityName && m_components.size() == cmp.m_components.size() && m_properties.size() == cmp.m_properties.size() &&
		m_properties == cmp.m_properties && m_components == cmp.m_components;
}
bool Entity::operator!=(const Entity& cmp) const
{
	return !(cmp == *this);
}

Entity& Entity::operator=(const Entity& ent)
{
	if (*this == ent)
		return *this;
	m_entityName = ent.m_entityName;
	m_properties = ent.m_properties;
	
	for (auto compType = ent.m_components.begin(); compType != ent.m_components.end(); ++compType)
	{
		for (auto cmp = compType->second.begin(); cmp != compType->second.end(); ++cmp)
		{
			m_components[compType->first].push_back((*cmp)->clone());
		}
	}
	/*for (auto comp = cmp.m_components.begin(); comp != cmp.m_components.end(); ++comp)
	{
		m_components[comp->first] = comp->second->clone();
	}*/
	return *this;
}

void updateCacheStatus(const ComponentType type, bool dirty)
{

}