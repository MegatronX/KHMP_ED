#include "EntityFactory.h"
#include <boost/make_shared.hpp>

//#include <character/StatManagerComponent.h>
//#include <character/StatusEffectsManager.h>

#include <iostream>

//using namespace KHMP;
EntityFactory* g_entityFactory = nullptr;
EntityFactory::EntityFactory() : m_idCounter(0), m_componentIDCounter(0)
{
	g_entityFactory = this;
}

EntityFactory::~EntityFactory()
{
	g_entityFactory = nullptr;
}


boost::shared_ptr<Entity> EntityFactory::createEntity(const std::string& entityName)
{
	auto entity = boost::make_shared<Entity>(getNextEntityID());

	if (entityName == "Character")
	{

	}

	return entity;
}
boost::shared_ptr<Entity> EntityFactory::createEntity(const std::string& entityType, const std::string& entityName)
{

	//boost::shared_ptr<Entity> entity;

	auto specificTypeCreator = m_entityNameSpecificCreators.find(entityType);
	if (specificTypeCreator != m_entityNameSpecificCreators.end())
	{
		auto specificCreator = specificTypeCreator->second.find(entityName);
		if (specificCreator != specificTypeCreator->second.end())
		{
			//return (*specificCreator)(entityType, entityName);
		}
	}
	auto creator = m_entityCreators.find(entityType);
	if (creator != m_entityCreators.end())
	{
		//entity = (*creator)();
		//return (*creator)(entityType, entityName);
	}
	auto ent = boost::make_shared<Entity>(getNextEntityID(), entityName);

	if (entityType == "Character")
	{
		//auto sm = boost::make_shared<StatManagerComponent>
	}

	return ent;
}
boost::shared_ptr<Entity> EntityFactory::createEntity(pugi::xml_node& entityNode)
{
	std::string entType(entityNode.name());
	auto creator = m_entityCreators.find(entType);
	boost::shared_ptr<Entity> entity;
	if (creator != m_entityCreators.end())
	{
		std::string entityName = entityNode.attribute("name").as_string();
		entity = creator->second(entityNode, *this);
		
	}
	else
	{
		std::string name(entityNode.attribute("name").value());
		entity = boost::make_shared<Entity>(getNextEntityID(), name);
		auto compsNode = entityNode.child("Components");
		if (compsNode)
		{
			for (auto comp = compsNode.begin(); comp != compsNode.end(); ++comp)
			{
				auto component = createComponent(*comp, entity.get());
				if (component.get() != nullptr)
				{
					entity->addComponent(component);
				}
			}
		}
		
	}
	entity->postInit();
	return entity;
}

boost::shared_ptr<Component> EntityFactory::createComponent(pugi::xml_node& compNode, Entity* owner, bool registerComponent, bool postInitComponent)
{
	std::string compName(compNode.name());
	auto creator = m_componentCreators.find(compName);
	boost::shared_ptr<Component> component;
	if (creator != m_componentCreators.end())
	{
		component = creator->second(compNode, owner, *this);
		if (owner != nullptr && component.get() != nullptr)
		{
			if (registerComponent)
			{
				owner->addComponent(component);
			}

			if (postInitComponent)
			{
				component->postInit();
			}
		}
	}
	else
	{
		std::cerr << "Could not find creation function for component name " + compName << "\n";
	}
	return component;
}

boost::shared_ptr<Component> EntityFactory::createComponent(const std::string& typeOverride, pugi::xml_node& node, Entity* owner)
{
	auto creator = m_componentCreators.find(typeOverride);
	boost::shared_ptr<Component> component;
	if (creator != m_componentCreators.end())
	{
		component = creator->second(node, owner, *this);
	}
	else
	{
		std::cerr << "Could not find creation function for component name " << node.name() << "\n";
	}
	return component;
}

bool EntityFactory::entityExists(const EntityID id) const
{
	return m_entityMap.find(id) != m_entityMap.end();
}

void EntityFactory::registerComponentCreator(const std::string& componentName, ComponentCreator creator)
{
	m_componentCreators[componentName] = creator;
}

void EntityFactory::registerComponentCreator(const ComponentType& componentType, ComponentCreator creator)
{
	m_componentCreatorsByType[componentType] = creator;
}
void EntityFactory::registerComponentCreator(const std::string& componentName, const ComponentType& type, ComponentCreator creator)
{
	registerComponentCreator(componentName, creator);
	registerComponentCreator(type, creator);
}

void EntityFactory::registerEntityCreator(const std::string& entityType, EntityCreator creator)
{
	m_entityCreators[entityType] = creator;
}

void EntityFactory::registerEntityCreator(const std::string& entityType, const std::string& entityName, EntityCreator creator)
{
	m_entityNameSpecificCreators[entityType][entityName] = creator;
}

EntityID EntityFactory::getNextEntityID()
{
	//++m_idCounter;
	return m_idCounter++;
}
ComponentID EntityFactory::getNextComponentID()
{
	return m_componentIDCounter++;
}
void EntityFactory::renameEntity(Entity* ent, const std::string& newName)
{
	if (ent != nullptr)
	{
		ent->m_entityName = newName;
	}
}
