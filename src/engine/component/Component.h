#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <SFML/Config.hpp>
#include <utilities/Cloneable.h>

class Entity;

typedef sf::Uint32 ComponentID;    //A unique id for a component. Each new component should have a different ID

//A unique id for each root component type. ComponentType is used to index components in an entity ->
//a given component type identifies a family of components that implement the same functionality
//have the same component type
typedef sf::Uint32 ComponentType;  

extern boost::unordered_map<std::string, ComponentType> ComponentStringTypeToType;
extern boost::unordered_map<ComponentType, std::string> ComponentTypeToTypeString;

class Component : public ICloneable<Component>
{
public:
	Component(const ComponentType& type = 0, const ComponentID& id = 0);
	Component(Entity& owner, const ComponentType& type = 0, const ComponentID& id = 0);
	Component(boost::shared_ptr<Entity> owner, const ComponentType& type = 0, const ComponentID& id = 0);
	Component(Entity* owner, const ComponentType& type = 0, const ComponentID& id = 0);
	//Component(const Component& copyFrom);
	
	virtual ~Component(); 

	virtual void init();// = 0;
	virtual void postInit();
	virtual void destroy();
	/*virtual const void init(pugi::xml_node& compNode) = 0;
	virtual void postInit(pugi::xml_node& rootNode) = 0;*/
	virtual const ComponentID getID() const
	{
		return m_id;
	}

	virtual const ComponentType getType() const
	{
		return m_type;
	}
	const Entity* getOwner() const;

	void setOwner(Entity* owner);

	bool ownedBy(const Entity* ent) const;

	virtual RawClonePtr rawClone() const
	{
		return new Component(*this);
	}

	bool addProperty(const std::string& key, const std::string& value, bool overwriteExisting = true);
	bool removeProperty(const std::string& key);
	bool hasProperty(const std::string& key);
	const std::string& getProperty(const std::string& key);
	//bool removeProperty(const std::string& key);

	bool hasFlag(const std::string& flag) const;
	bool addFlag(const std::string& flag);
	bool removeFlag(const std::string& flag);

	//special functionality. Try to avoid over use
	Component* getComponent(const ComponentType type) const
	{
		auto it = m_subComponents.find(type);
		if (it != m_subComponents.end())
		{
			if (it->second)
			{
				return it->second.get();
			}
		}
		return nullptr;
	}

	template <class T>
	T* getComponentAs(const ComponentType type) const
	{
		auto cmp = getComponent(type);
		return cmp == nullptr ? nullptr : dynamic_cast<T*>(cmp);
	}
	bool hasComponent(const ComponentType type) const;
	bool addComponent(boost::shared_ptr<Component> component, const bool initComponent, const bool postInitComponent, const bool overwriteExisting = true);
	bool removeComponent(const ComponentType type, const ComponentID id, bool destroyComponent = true);

	bool operator==(const Component& cmp) const;
	bool operator!=(const Component& cmp) const;
	//bool areSameType(const Component& cmp) const;
	//Component& operator=(const Component& cmp);
	const static std::string m_emptyProperty;
protected:
	Entity* m_owner;
	ComponentID m_id;
	ComponentType m_type;
	boost::unordered_map<ComponentType, boost::shared_ptr<Component> > m_subComponents;
	boost::unordered_map<std::string, std::string> m_properties;
	boost::unordered_set<std::string> m_flags;

	bool m_initialized;
	bool m_destroyed;
};

#endif