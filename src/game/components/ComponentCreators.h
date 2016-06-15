#pragma once
#ifndef _COMPONENTCREATORS_H_
#define _COMPONENTCREATORS_H_

#include <component/Component.h>
#include <input/files/xml/pugixml.hpp>

class Entity;
class EntityFactory;
namespace KHMP
{
	extern void registerComponentCreators(EntityFactory& registerTo);

	extern boost::shared_ptr<Component> createStatComponent(pugi::xml_node&, Entity* owner, EntityFactory&);
	extern boost::shared_ptr<Component> createStatManagerComponent(pugi::xml_node&, Entity* owner, EntityFactory&);
	extern boost::shared_ptr<Component> createElementalComponent(pugi::xml_node&, Entity* owner, EntityFactory&);
	extern boost::shared_ptr<Component> createCharacterComponent(pugi::xml_node&, Entity* owner, EntityFactory&);
	extern boost::shared_ptr<Component> createBattleCharacterComponent(pugi::xml_node&, Entity* owner, EntityFactory&);
	extern boost::shared_ptr<Component> createActionComponent(pugi::xml_node&, Entity* owner, EntityFactory&);
	extern boost::shared_ptr<Component> createAttackComponent(pugi::xml_node&, Entity* owner, EntityFactory&);
}

#endif