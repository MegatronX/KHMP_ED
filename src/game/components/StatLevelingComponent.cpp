#include <components/StatLevelingComponent.h>
#include <events/LevelChangeEvent.h>
#include <log/Log.h>
namespace KHMP
{
	
	StatLevelingComponent::StatLevelingComponent(Entity* owner)
	{

	}

	bool StatLevelingComponent::handleLevelChangeEvent(ev_ptr event)
	{
		bool handled = false;
		if (event->getEventType() == LevelChangeEvent::m_eventSignature)
		{
			auto lvEvent = boost::dynamic_pointer_cast<LevelChangeEvent>(event);
			if (lvEvent->getCharacter() == this->getOwner())
			{
				for (unsigned int stat = 0; stat < StatCount; ++stat)
				{
					int statval = getStatValueForLevel(static_cast<Stat>(stat), lvEvent->getNewLevel());
					
				}
			}
		}
		return handled;
	}

	int StatLevelingComponent::getStatValueForLevel(const Stat stat, const unsigned int level)
	{
		int finalstatval = 0;
		auto& leveler = m_statLevelers[static_cast<unsigned int>(stat)];
		if (leveler.m_useExpression)
		{
			/*mu::value_type leveltmp = level;
			m_parser.SetExpr(leveler.m_expression);
			m_parser.DefineVar("level", &leveltmp);
			std::string nametemp = m_owner->getEntityName();
			m_parser.DefineStrConst("character", nametemp);
			mu::value_type statval = m_parser.Eval();
			finalstatval = statval;*/
		}
		else
		{
			if (level > leveler.m_statMap.size())
			{
				LOG_DEBUG("Tried to access stat " << StatNameLookup.find(stat)->second << " at level " << level << " but only levels up to "
					<< leveler.m_statMap.size() << " are available for " << (m_owner ? m_owner->getEntityName() : " NULL\n"));
			}
			else
			{
				finalstatval = leveler.m_statMap[level];
			}
		}
		return finalstatval;
	}
}