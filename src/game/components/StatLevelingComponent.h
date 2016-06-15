#pragma once
#ifndef _STATLEVELINGCOMPONENT_H_
#define _STATLEVELINGCOMPONENT_H_

#include <entity/Entity.h>
#include <events/IEvent.h>
#include <character/Stats.h>
#include <muparser/muparser.h>

namespace KHMP
{
	struct StatLevelerEntry
	{
		std::string m_expression;
		boost::unordered_map<unsigned int, unsigned int> m_statMap;
		bool m_useExpression;
	};
	class StatLevelingComponent : public Component
	{
	public:
		StatLevelingComponent(Entity* owner);

		bool handleLevelChangeEvent(ev_ptr event);

		int getStatValueForLevel(const Stat stat, const unsigned int level);

	protected:
		int m_ownerLevel;
		//mu::Parser m_parser;
		std::array<StatLevelerEntry, StatCount> m_statLevelers;
	private:
		

	};
}
#endif