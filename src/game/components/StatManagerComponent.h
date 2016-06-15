#pragma once
#ifndef _STATMANAGERCOMPONENT_H_
#define _STATMANAGERCOMPONENT_H_
//#include <component/Component.h>
#include <map>
#include <boost/functional/hash.hpp>

#include <components/StatComponent.h>
#include <character/Stats.h>
#include <events/IEvent.h>

class IEventManager;

namespace KHMP
{
	
	
	struct StatLimiter
	{
		StatLimiter();
		int m_statLevel;
		boost::unordered_map<int, int> m_statLimit;
		int getStatLimit() const;
		int getStatLimit(const int statLevel) const;
	};
	const unsigned int statModes = 2;
	class StatManagerComponent : public Component
	{
	public:
		const static ComponentType m_componentType = 0x128c6338;// , 0xd08c, 0x4af5, 0x81, 0x18, 0xe2, 0x37, 0x14, 0x80, 0xc2, 0x5b);

		StatManagerComponent(Entity* owner, ComponentID id);
		StatManagerComponent(const StatManagerComponent& ref);
		~StatManagerComponent();

		void syncPreviewToNormalAllStats();
		void syncPreviewToNormal(const unsigned int stat);
		void syncPreviewToNormal(const Stat stat);

		void syncNormalToPreviewAllStats();
		void syncNormalToPreview(const Stat stat);
		void syncNormalToPreview(const unsigned stat);

		void syncStat(const Stat stat, const StatMode mode);
		void syncStat(const unsigned int stat, const StatMode mode = Normal);
		void syncAllStats();

		int getCurrentHP() const;
		int getCurrentMP() const;
		int getCurrentSP() const;

		bool handleStatChangeRequest(ev_ptr statChangeEvent);
		bool handleNewStatGroupRequest(ev_ptr newStatGroupRequest);

		void addStatLimiter(const Stat stat, const int limitLevel, const int limit);
		void removeStatLimiter(const Stat stat, const int limitLevel, const int limit);
		int getStatLimitLevel(const Stat stat) const;
		int getStatLimitAtLevel(const Stat stat, const int level) const;
		int getCurrentStatLimit(const Stat stat) const;

		int getStat(bool& validReturn, const Stat stat, const std::string& statGroup = "raw");

		StatComponent& getStatComponent(bool& validReturn, const std::string& statGroup = "raw");

		void registerEventHandlers(IEventManager* mng);
	protected:
		void dispatchStatChangedEvent(const Stat stat, const int oldVal, const int newVal, bool volatileStatChange);
		
	private:
		StatMode m_activeMode;

		//Root stats -> stats from level/root decisions during character creation
		StatComponent m_rawStats;
		//Stats seperate from level/root decisions but which are permanently tied to the character
		StatComponent m_permanentStatBoosts;

		//Combined raw + permanent boosts. 
		StatComponent m_baseStats;

		//additional stat boosters sorted by priority -> higher priority = first application to stats
		std::map<int, boost::unordered_map<std::string, StatComponent> > m_additionalStats;
		boost::unordered_map<int, StatComponent*> m_additionalStatsByIndex;
		//Stats after all previous multiplers/adders are combined. These are the characters display stats and are used to initialize
		//the character's battle stats
		StatComponent m_effectiveStats;

		std::array<bool, StatCount> m_enforceStatLimits;
		std::array<int, StatCount> m_statLimitLevels;
		std::map<int, std::array<int, StatCount> > m_statLimits;
		//Voaltile stats
		/*std::array<int, statModes> m_currentHP;
		std::array<int, statModes> m_currentMP;
		std::array<int, statModes> m_currentSP;
		//Stats controlled by level
		std::array<std::array<int, StatCount>, statModes> m_rawStats;
		std::array<std::array<int, StatCount>, statModes> m_permanentStatBoosts;
		//Raw stats + permanent Stat boosts
		std::array<std::array<int, StatCount>, statModes> m_baseStats;
		//Multipliers to base stats
		std::array<std::array<float, StatCount>, statModes> m_baseStatMultipliers;
		//Stat adders that are not permanent and may be controlled by external sources i.e. status effects, abilities, equipment etc.
		boost::unordered_map<std::string, std::array<std::array<int, StatCount>, statModes> > m_additionalStatAdders;

		//Effective stats outside of battle. Addition of base stats + any additional adders + base stat multipliers
		std::array<std::array<int, StatCount>, statModes> m_referenceStats;

		//Multipliers to references stats. That is, multipliers that act on stats after all adders + base multipliers
		std::array<std::array<float, StatCount>, statModes> m_referenceStatMultipliers;
		//External multipliers to references stats. That is, multipliers that act on stats after all adders + base multipliers
		boost::unordered_map<std::string, std::array<std::array<float, StatCount>, statModes> > m_additionalReferenceStatMultipliers;

		

		//effective stats after all multipliers + adders are combined
		std::array<std::array<int, StatCount>, statModes> m_effectiveStats;

		std::array<StatLimiter, StatCount> m_statLimits;*/
		const static boost::hash<std::string> matchHasher;
		IEventManager* m_evMng;
		bool m_registered;
	};
}

#endif