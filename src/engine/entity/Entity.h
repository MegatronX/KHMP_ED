#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <string>
#include <vector>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/lexical_cast.hpp>

#include <sfml/Config.hpp>
#include <component/Component.h>
#include <utilities/Cloneable.h>
#include <utilities/PropertyManager.h>

typedef sf::Uint32 EntityID;

class Entity : public ICloneable<Entity>, public PropertyManager
{
public:
	explicit Entity(const EntityID id);
	explicit Entity(const EntityID id, const std::string& entityName);
	Entity(const Entity& ref);
	virtual ~Entity();

	virtual void initEntity();
	virtual void destroyEntity();
	virtual void postInit();

	Component* getComponent(const ComponentID id) const
	{
		auto it = m_componentsByID.find(id);
		if (it != m_componentsByID.end())
		{
			if (it->second)
			{
				return it->second;
			}
		}
		return nullptr;
	}

	template <class T>
	T* getComponentAs(const ComponentID id) const
	{
		auto cmp = getComponent(id);
		return cmp == nullptr ? nullptr : dynamic_cast<T*>(cmp);
	}

	std::vector<Component*> getComponents(const ComponentType type) const
	{
		/*auto cachedRes = m_componentsCache.find(type);
		if (cachedRes != m_componentsCache.end() && !(cachedRes->second.first))
		{
			return cachedRes->second.second;
		}*/
		std::vector<Component*> cmps;
		auto it = m_components.find(type);
		if (it != m_components.end())
		{
			cmps.reserve(it->second.size());
			for (auto cmp = it->second.begin(); cmp != it->second.end(); ++cmp)
			{
				cmps.push_back(cmp->get());
			}
		}
		/*if (cmps.size() > 0)
		{
			m_componentsCache[type].first = false;
			m_componentsCache[type].second = cmps;
		}
		else if (cachedRes != m_componentsCache.end())
		{
			m_componentsCache.erase(cachedRes);
		}*/
		//m_componentCache[type] = cmps;
		return cmps;
		/*if (!m_cacheDirty)
		{
			auto it = m_componentCache.find(type);
			if (it != m_componentCache.end())
				return it->second;
		}
		else
		{
			m_componentCache.clear();
		}
		std::vector<Component*> cmps;
		auto it = m_components.find(type);
		if (it != m_components.end())
		{
			cmps.reserve(it->second.size());
			for (auto cmp = it->second.begin(); cmp != it->second.end(); ++cmp)
			{
				cmps.push_back(cmp->get());
			}
		}
		m_componentCache[type] = cmps;
		return cmps;*/
	}

	template <class T>
	std::vector<T*> getComponentsAs(const ComponentType type) const
	{
		std::vector<T*> cmps;
		auto cmpSet = getComponents(type);
		if (cmpSet.size() > 0)
		{
			for (auto cmp = cmpSet.begin(); cmp != cmpSet.end(); ++cmp)
			{
				auto cmpPtr = dynamic_cast<T*>(*cmp);
				if (cmpPtr != nullptr)
				{
					cmps.push_back(cmpPtr);
				}
			}
		}
		return cmps;// cmpPtr == NULL ? NULL : dynamic_cast<T*>(cmpPtr);
	}
	bool hasComponent(const ComponentID id) const;
	bool hasComponents(const ComponentType type) const;
	int getComponentCount(const ComponentType type) const;
	int getComponentCount() const;
	bool addComponent(boost::shared_ptr<Component> component, const bool overwriteExisting = true);
	//Note that this function passes ownership of the component to this entity. The entity will assume any other references to this component are temporary/not shared
	bool addComponent(Component* component, const bool overwriteExisting = true);
	bool addComponent(boost::shared_ptr<Component> component, const bool initComponent, const bool postInitComponent, const bool overwriteExisting = true);
	bool addComponent(Component* component, const bool initComponent, const bool postInitComponent, const bool overwriteExisting = true);
	
	bool addComponentAsOnlyInstanceOfType(boost::shared_ptr<Component> component, const bool initComponent = true, const bool postInitComponent = true);

	bool removeComponent(const ComponentType type, const ComponentID id, bool destroyComponent = true);
	bool removeComponents(const ComponentType types, bool destroyComponents = true);
	bool removeComponent(const ComponentID id, bool destroyComponent = true);
	bool removeComponent(const Component* component, bool destroyComponent = true);
	bool removeComponent(const boost::shared_ptr<Component> component, bool destroyComponent = true);
	bool removeComponent(const Component& component, bool destroyComponent = true);


	bool hasProperty(const std::string& property) const;
	bool addProperty(const std::string& property, const std::string& value, const bool overwriteExisting = true);
	std::string getProperty(const std::string& property) const;
	bool removeProperty(const std::string& property);

	template <class T>
	T getPropertyAs(const std::string& property, bool& validGet) const
	{
		if (hasProperty(property))
		{
			validGet = true;
			return boost::lexical_cast<T>(getProperty(property));
		}
		else
		{
			validGet = false;
			return boost::lexical_cast<T>("0");
		}
	}

	bool hasFlag(const std::string& flag) const;
	bool addFlag(const std::string& flag);
	bool removeFlag(const std::string& flag);

	const std::string& getEntityName() const;

	void setEntityName(const std::string& name);

	virtual RawClonePtr rawClone() const override;

	bool operator==(const Entity& cmp) const;
	bool operator!=(const Entity& cmp) const;
	Entity& operator=(const Entity& cmp);

protected:
	//void updateCacheStatus(const ComponentType type, bool dirty);
private:
	boost::unordered_map<ComponentType, std::vector<boost::shared_ptr<Component> > > m_components;
	boost::unordered_map< ComponentID, Component*> m_componentsByID;
	boost::unordered_map<std::string, std::string> m_properties;
	boost::unordered_set<std::string> m_flags;

	boost::unordered_map<ComponentType, std::pair<bool, std::vector<Component*> > > m_componentsCache;

	/*boost::unordered_map<ComponentType, std::vector<Component*> > m_componentCache;
	bool m_cacheDirty;*/

	std::string m_entityName;
	EntityID m_id;
	friend class EntityFactory;
};

typedef boost::shared_ptr<Entity> entity_ptr;

#endif