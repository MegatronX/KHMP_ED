#include <databases/EntityDatabase.h>

namespace KHMP
{
	EntityDatabase::EntityDatabase()
	{

	}
	EntityDatabase::~EntityDatabase()
	{

	}

	bool EntityDatabase::addEntry(entity_ptr ent)
	{
		if (ent)
		{
			std::string name = ent->getEntityName();
			auto entryAvailable = m_dbEntriesByName.find(name);
			m_dbEntriesByName[name] = ent;
			//m_dbEntriesByID[ent->getID]
			
		}
		return true;
	}
	entity_ptr EntityDatabase::getEntryByName(const std::string& entityName)
	{
		entity_ptr entry = nullptr;
		auto it = m_dbEntriesByName.find(entityName);
		if (it != m_dbEntriesByName.end())
		{
			entry = it->second;
		}
		return entry;
	}
	/*Entity* EntityDatabase::getEntryByID(const ComponentID id)
	{
		Entity* entry = nullptr;
		auto it = m_dbEntriesByID.find(id);
		if (it != m_dbEntriesByID.end())
		{
			entry = it->second;
		}
		return entry;
	}*/


	bool EntityDatabase::validateEntry(entity_ptr entity) const
	{
		return entity.get() != nullptr;
	}
}