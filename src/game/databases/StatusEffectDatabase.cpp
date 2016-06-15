#include <databases/StatusEffectDatabase.h>

namespace KHMP
{
	bool StatusEffectDatabase::validateEntry(entity_ptr se) const
	{
		return EntityDatabase::validateEntry(se) && se->hasComponents(StatusEffectComponent::m_componentType);
	}
}