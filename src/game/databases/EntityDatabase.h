#pragma once
#ifndef _ENTITYDATABASE_H_
#define _ENTITYDATABASE_H_

#include <entity/Entity.h>

namespace KHMP
{
	class EntityDatabase
	{
	public:
		EntityDatabase();
		virtual ~EntityDatabase();
		virtual bool addEntry(entity_ptr ent);
		virtual entity_ptr getEntryByName(const std::string& entityName);
		//virtual Entity* getEntryByID(const ComponentID id);
	protected:
		virtual bool validateEntry(entity_ptr entity) const;
	private:
		boost::unordered_map<std::string, entity_ptr> m_dbEntriesByName;
		boost::unordered_map<ComponentID, Entity*> m_dbEntriesByID;
		boost::unordered_map<ComponentType, boost::unordered_map<std::string, Entity*>> m_dbEntriesByType;
	};
}

#endif