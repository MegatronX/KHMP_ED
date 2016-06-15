#pragma once
#ifndef _STATCOMPONENT_H_
#define _STATCOMPONENT_H_

#include <component/Component.h>
#include <array>
#include <character/Stats.h>
namespace KHMP
{
	
	class StatComponent : public Component
	{
	public:
		const static ComponentType m_componentType = 0xc19f242f;// , 0xf82d, 0x4550, 0x87, 0x98, 0x26, 0x6d, 0xe9, 0xf9, 0x45, 0x13);

		StatComponent();
		StatComponent(Entity* owner, const ComponentID id);

		RawClonePtr rawClone() const override;

		int getStatValue(const Stat stat, bool includeMultiplier = true) const;
		float getStatMultiplier(const Stat stat) const;
		void setStatValue(const Stat stat, int statVal);
		void copyStatValues(const StatComponent& refStats, const bool allModes = false);
		void copyStatValues(const std::array<int, StatCount>& refStats);
		void copyStatMultipliers(const std::array<float, StatCount>& refMult);

		void addStatValues(const StatComponent& refStats, const bool allModes = false);
		void addStatValues(const std::array<int, StatCount>& addStats);
		void addStatValues(const std::array<int, StatCount>& addStats, StatMode mode);
		void addStatValues(const std::array<float, StatCount>& refMult);
		void addStatValues(const std::array<float, StatCount>& mulStats, StatMode mode);
		void addStatValues(const std::array<int, StatCount>& addStats, const std::array<float, StatCount>& mulStats);
		void addStatValues(const std::array<int, StatCount>& addStats, const std::array<float, StatCount>& mulStats, StatMode mode);

		void setStatMultiplier(const Stat stat, float mult);
		void setStatMode(StatMode mode);

		void syncStatMode(const Stat stat, const StatMode modeSrc, const StatMode modeDest);
		void syncAllStatsMode(const StatMode modeSrc, const StatMode modeDest);
		const std::array<int, StatCount>& getStats() const;
		const std::array<int, StatCount>& getStats(const StatMode mode) const;

		const std::array<float, StatCount>& getMultipliers() const;
		const std::array<float, StatCount>& getMultipliers(const StatMode mode) const;

		void remapStat(const Stat initialStat, const Stat endStat, const bool sync = true);
		void clearStatRemap(const Stat stat);
		void clearAllRemaps();
		Stat getMappedStat(const Stat stat) const;
		friend StatComponent operator+(const StatComponent& cmp1, const StatComponent& cmp2);
	protected:
	private:
		std::array<std::array<int, StatCount>, StatModes> m_stats;
		std::array<std::array<float, StatCount>, StatModes> m_multipliers;
		boost::unordered_map<Stat, Stat> m_statRemaps;
		StatMode m_mode;
		float m_baseMult;
	};
}

#endif