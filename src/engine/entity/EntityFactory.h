#pragma once
#ifndef _ENTITYFACTORY_H_
#define _ENTITYFACTORY_H_

#include <entity/Entity.h>
#include <input/files/xml/pugixml.hpp>

class EntityFactory;

typedef boost::shared_ptr<Component>(*ComponentCreator)(pugi::xml_node&, Entity* owner, EntityFactory&);
typedef boost::shared_ptr<Entity>(*EntityCreator)(pugi::xml_node&, EntityFactory&);

extern EntityFactory* g_entityFactory;

class EntityFactory
{
public:

	EntityFactory();
	virtual ~EntityFactory();
	
	boost::shared_ptr<Entity> createEntity(const std::string& entityName);
	//Used to create some basic entity types
	virtual boost::shared_ptr<Entity> createEntity(const std::string& entityType, const std::string& entityName);

	virtual boost::shared_ptr<Entity> createEntity(pugi::xml_node& entityNode);

	boost::shared_ptr<Component> createComponent(pugi::xml_node& compNode, Entity* owner, bool registerComponent = false, bool postInitComponent = false);
	boost::shared_ptr<Component> createComponent(const std::string& typeOverride, pugi::xml_node& node, Entity* owner);
	bool entityExists(const EntityID id) const;

	void registerComponentCreator(const std::string& componentName, ComponentCreator creator);
	void registerComponentCreator(const ComponentType& componentType, ComponentCreator creator);
	void registerComponentCreator(const std::string& componentName, const ComponentType& type, ComponentCreator creator);
	void registerEntityCreator(const std::string& entityType, EntityCreator creator);
	void registerEntityCreator(const std::string& entityType, const std::string& entityName, EntityCreator creator);

	EntityID getNextEntityID();
	ComponentID getNextComponentID();
	void renameEntity(Entity* ent, const std::string& newName);
protected:

private:
	boost::unordered_map<EntityID, std::weak_ptr<Entity> > m_entityMap;
	boost::unordered_map<std::string, ComponentCreator> m_componentCreators;
	boost::unordered_map<ComponentType, ComponentCreator> m_componentCreatorsByType;
	boost::unordered_map<std::string, EntityCreator> m_entityCreators;
	boost::unordered_map<std::string, boost::unordered_map<std::string, EntityCreator> > m_entityNameSpecificCreators;
	EntityID m_idCounter;
	ComponentID m_componentIDCounter;
};

#endif