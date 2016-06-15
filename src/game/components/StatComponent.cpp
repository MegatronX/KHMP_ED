#include "StatComponent.h"

namespace KHMP
{
	StatComponent::StatComponent() : Component(m_componentType, -1)
	{

	}
	StatComponent::StatComponent(Entity* owner, const ComponentID id) : Component(owner, m_componentType, id),
		m_mode(Normal), m_baseMult(1.f), m_stats(), m_multipliers()
	{

	}

	StatComponent::RawClonePtr StatComponent::rawClone() const
	{
		return RawClonePtr(new StatComponent(*this));
	}

	int StatComponent::getStatValue(const Stat stat, bool includeMultiplier) const
	{
		//FIX
		Stat trueStat = stat;// =
		int statVal = m_stats[m_mode][stat];
		return includeMultiplier ? static_cast<int>(static_cast<float>(statVal) * (m_baseMult + m_multipliers[m_mode][stat])) : statVal;
	}
	void StatComponent::copyStatValues(const StatComponent& refStats, const bool allModes)
	{
		if (!allModes)
		{
			m_stats[m_mode] = refStats.getStats(m_mode);
			m_multipliers[m_mode] = refStats.getMultipliers(m_mode);
		}
		else
		{
			m_stats[Normal] = refStats.getStats(Normal);
			m_multipliers[Normal] = refStats.getMultipliers(Normal);
			m_stats[Preview] = refStats.getStats(Preview);
			m_multipliers[Preview] = refStats.getMultipliers(Preview);
		}
	}
	void StatComponent::copyStatValues(const std::array<int, StatCount>& refStats)
	{
		m_stats[m_mode] = refStats;
	}
	void StatComponent::copyStatMultipliers(const std::array<float, StatCount>& refMult)
	{
		m_multipliers[m_mode] = refMult;
	}

	void StatComponent::addStatValues(const StatComponent& refStats, const bool allModes)
	{
		if (allModes)
		{
			addStatValues(refStats.getStats(), refStats.getMultipliers(), StatMode::Normal);
			addStatValues(refStats.getStats(), refStats.getMultipliers(), StatMode::Preview);
		}
		else
		{
			addStatValues(refStats.getStats(), refStats.getMultipliers());
		}
	}
	void StatComponent::addStatValues(const std::array<int, StatCount>& addStats)
	{
		addStatValues(addStats, m_mode);
	}
	void StatComponent::addStatValues(const std::array<int, StatCount>& addStats, StatMode mode)
	{
		int modeSlot = static_cast<unsigned int>(mode);
		for (unsigned int stat = 0; stat < StatCount; ++stat)
		{
			m_stats[modeSlot][stat] += addStats[stat];
		}
	}
	void StatComponent::addStatValues(const std::array<float, StatCount>& refMult)
	{
		addStatValues(refMult, m_mode);
	}
	void StatComponent::addStatValues(const std::array<float, StatCount>& mulStats, StatMode mode)
	{
		int modeSlot = static_cast<unsigned int>(mode);
		for (unsigned int stat = 0; stat < StatCount; ++stat)
		{
			m_multipliers[modeSlot][stat] += mulStats[modeSlot];
			//m_stats[modeSlot][stat] += addStats[stat];
		}
	}
	void StatComponent::addStatValues(const std::array<int, StatCount>& addStats, const std::array<float, StatCount>& mulStats)
	{
		addStatValues(addStats, mulStats, m_mode);
	}
	void StatComponent::addStatValues(const std::array<int, StatCount>& addStats, const std::array<float, StatCount>& mulStats, StatMode mode)
	{
		addStatValues(addStats, mode);
		addStatValues(mulStats, mode);
	}

	float StatComponent::getStatMultiplier(const Stat stat) const
	{
		return m_multipliers[m_mode][stat];
	}
	void StatComponent::setStatValue(const Stat stat, int statVal)
	{
		m_stats[m_mode][stat] = statVal;
	}
	void StatComponent::setStatMultiplier(const Stat stat, float mult)
	{
		m_multipliers[m_mode][stat] = mult;
	}
	void StatComponent::setStatMode(StatMode mode)
	{
		m_mode = mode;
	}
	void StatComponent::syncAllStatsMode(const StatMode modeSrc, const StatMode modeDest)
	{
		for (unsigned int stat = 0; stat < StatCount; ++stat)
		{
			syncStatMode(static_cast<Stat>(stat), modeSrc, modeDest);
		}
	}
	void StatComponent::syncStatMode(const Stat stat, const StatMode modeSrc, const StatMode modeDest)
	{
		m_stats[modeDest][stat] = m_stats[modeSrc][stat];
		m_multipliers[modeDest][stat] = m_multipliers[modeSrc][stat];
	}

	const std::array<int, StatCount>& StatComponent::getStats() const
	{
		return getStats(m_mode);
	}
	const std::array<int, StatCount>& StatComponent::getStats(const StatMode mode) const
	{
		return m_stats[mode];
	}

	const std::array<float, StatCount>& StatComponent::getMultipliers() const
	{
		return getMultipliers(m_mode);
	}
	const std::array<float, StatCount>& StatComponent::getMultipliers(const StatMode mode) const
	{
		return m_multipliers[mode];
	}

	void StatComponent::remapStat(const Stat initialStat, const Stat endStat, const bool sync)
	{
		clearStatRemap(initialStat);
		clearStatRemap(endStat);
		m_statRemaps[initialStat] = endStat;
		int temp = m_stats[m_mode][initialStat];
		m_stats[m_mode][initialStat] = m_stats[m_mode][endStat];
		m_stats[m_mode][endStat] = temp;

		float mtemp = m_multipliers[m_mode][initialStat];
		m_multipliers[m_mode][initialStat] = m_multipliers[m_mode][endStat];
		m_multipliers[m_mode][endStat] = mtemp;
	}
	
	void StatComponent::clearStatRemap(const Stat stat)
	{
		auto mappedStat = m_statRemaps.find(stat);
		if (mappedStat != m_statRemaps.end())
		{
			int curVal = m_stats[m_mode][mappedStat->first];
			m_stats[m_mode][mappedStat->first] = m_stats[m_mode][mappedStat->second];
			m_stats[m_mode][mappedStat->second] = curVal;

			float curMul = m_multipliers[m_mode][mappedStat->first];
			m_multipliers[m_mode][mappedStat->first] = m_multipliers[m_mode][mappedStat->second];
			m_multipliers[m_mode][mappedStat->second] = curMul;

			m_statRemaps.erase(mappedStat);
		}
	}
	void StatComponent::clearAllRemaps()
	{
		for (auto mappedstat = m_statRemaps.begin(); mappedstat != m_statRemaps.end();)
		{
			int curVal = m_stats[m_mode][mappedstat->first];
			m_stats[m_mode][mappedstat->first] = m_stats[m_mode][mappedstat->second];
			m_stats[m_mode][mappedstat->second] = curVal;

			float curMul = m_multipliers[m_mode][mappedstat->first];
			m_multipliers[m_mode][mappedstat->first] = m_multipliers[m_mode][mappedstat->second];
			m_multipliers[m_mode][mappedstat->second] = curMul;

			mappedstat = m_statRemaps.erase(mappedstat);
		}
	}

	Stat StatComponent::getMappedStat(const Stat stat) const
	{
		auto sm = m_statRemaps.find(stat);
		return sm == m_statRemaps.end() ? stat : sm->second;
	}
	/*StatComponent StatComponent::operator+(const StatComponent& cmp1, , const StatComponent& cmp2)
	{
		StatComponent cmp(owner, )
	}*/
}