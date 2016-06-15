#pragma once
#ifndef _GAMEENTITYFACTORY_H_
#define _GAMEENTITYFACTORY_H_

#include <entity/EntityFactory.h>

namespace KHMP
{

	extern boost::shared_ptr<Entity> StatusEffectCreator(pugi::xml_node&, EntityFactory&);
	extern boost::shared_ptr<Component> StatChangeOnApplyComponenetCreator(pugi::xml_node&, Entity* owner, EntityFactory&);
	class GameEntityFactory : public EntityFactory
	{
	public:
		GameEntityFactory();
		virtual ~GameEntityFactory();

		boost::unordered_map<std::string, boost::shared_ptr<Entity> > parseEquipmentDatabase(const std::string& equipDoc);
		boost::unordered_map<std::string, boost::shared_ptr<Entity> > parseStatusEffectDatabase(const std::string& seDoc);
		virtual boost::shared_ptr<Entity> createEntity(const std::string& entityType, const std::string& entityName) override;
		virtual boost::shared_ptr<Entity> createEntity(pugi::xml_node& entity) override;
	protected:
	private:
	};
}

#endif