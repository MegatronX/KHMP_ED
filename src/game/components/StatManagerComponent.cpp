#include "StatManagerComponent.h"
#include <events/StatChangeEvent.h>
#include <boost/algorithm/string.hpp>
#include <events/IEventManager.h>
namespace KHMP
{
	const boost::hash<std::string> StatManagerComponent::matchHasher = boost::hash<std::string>();
	int StatLimiter::getStatLimit() const
	{
		return getStatLimit(m_statLevel);
	}
	int StatLimiter::getStatLimit(const int statLevel) const
	{
		auto limiter = m_statLimit.find(statLevel);
		return limiter != m_statLimit.end() ? limiter->second : NoStatLimit;
	}
	StatManagerComponent::StatManagerComponent(Entity* owner, ComponentID id) : Component(owner, m_componentType, id), 
		m_rawStats(owner, id), m_permanentStatBoosts(owner, id), m_baseStats(owner, id), m_effectiveStats(owner, id), m_enforceStatLimits(), 
		m_additionalStats(), m_registered(false), m_evMng(nullptr)
		//, m_referenceStatMultipliers(), m_referenceStats(),
		//m_additionalReferenceStatMultipliers(), m_baseStatMultipliers(), m_baseStats(), m_additionalStatAdders(), m_effectiveStats(), m_activeMode(Normal)
	{

	}
	StatManagerComponent::StatManagerComponent(const StatManagerComponent& ref) : Component(ref), m_rawStats(ref.m_rawStats), m_permanentStatBoosts(ref.m_permanentStatBoosts), m_baseStats(ref.m_baseStats), 
		m_effectiveStats(ref.m_effectiveStats), m_enforceStatLimits(ref.m_enforceStatLimits), m_additionalStats(ref.m_additionalStats), m_registered(false), m_evMng(nullptr)
	{

	}
	StatManagerComponent::~StatManagerComponent()
	{
		if (m_evMng != nullptr && m_registered)
		{
			m_evMng->removeListener(fastdelegate::MakeDelegate(this, &StatManagerComponent::handleStatChangeRequest), BatchStatChangeRequest::m_eventSignature);
			m_evMng->removeListener(fastdelegate::MakeDelegate(this, &StatManagerComponent::handleStatChangeRequest), SingleStatChangeRequest::m_eventSignature);
		}
	}
	void StatManagerComponent::syncPreviewToNormalAllStats()
	{
		for (unsigned int stat = 0; stat < StatCount; ++stat)
		{
			syncPreviewToNormal(stat);
		}
	}
	void StatManagerComponent::syncPreviewToNormal(const unsigned int stat)
	{
		syncPreviewToNormal(static_cast<Stat>(stat));
	}
	void StatManagerComponent::syncPreviewToNormal(const Stat stat)
	{
		/*m_baseStats[Normal] = m_baseStats[Preview];
		m_baseStatMultipliers[Normal] = m_baseStatMultipliers[Preview];
		for (auto statAdders = m_additionalStatAdders.begin(); statAdders != m_additionalStatAdders.end(); ++statAdders)
		{
			statAdders->second[Normal] = statAdders->second[Preview];
		}
		m_referenceStats[Normal] = m_referenceStats[Preview];
		for (auto statMul = m_additionalReferenceStatMultipliers.begin(); statMul != m_additionalReferenceStatMultipliers.end(); ++statMul)
		{
			statMul->second[Normal] = statMul->second[Preview];
		}
		m_effectiveStats[Normal] = m_effectiveStats[Preview];*/
	}

	void StatManagerComponent::syncNormalToPreviewAllStats()
	{
		for (unsigned int stat = 0; stat < StatCount; ++stat)
		{
			syncNormalToPreview(stat);
		}
	}
	void StatManagerComponent::syncNormalToPreview(const Stat stat)
	{
		/*m_baseStats[Preview] = m_baseStats[Normal];
		m_baseStatMultipliers[Preview] = m_baseStatMultipliers[Normal];
		for (auto statAdders = m_additionalStatAdders.begin(); statAdders != m_additionalStatAdders.end(); ++statAdders)
		{
			statAdders->second[Preview] = statAdders->second[Normal];
		}
		m_referenceStats[Preview] = m_referenceStats[Normal];
		for (auto statMul = m_additionalReferenceStatMultipliers.begin(); statMul != m_additionalReferenceStatMultipliers.end(); ++statMul)
		{
			statMul->second[Preview] = statMul->second[Normal];
		}
		m_effectiveStats[Preview] = m_effectiveStats[Normal];*/
	}
	void StatManagerComponent::syncNormalToPreview(const unsigned stat)
	{
		syncNormalToPreview(static_cast<Stat>(stat));
	}

	void StatManagerComponent::syncStat(const Stat stat, const StatMode mode)
	{
		int runningStat = m_rawStats.getStatValue(stat) + static_cast<int>(static_cast<float>(m_permanentStatBoosts.getStatValue(stat, false)) * m_permanentStatBoosts.getStatMultiplier(stat));
		m_baseStats.setStatValue(stat, runningStat);
		runningStat = static_cast<int>(static_cast<float>(runningStat) * m_baseStats.getStatMultiplier(stat));
		for (auto statSetPriority = m_additionalStats.begin(); statSetPriority != m_additionalStats.end(); ++statSetPriority)
		{
			for (auto statSet = statSetPriority->second.begin(); statSet != statSetPriority->second.end(); ++statSet)
			{
				runningStat += statSet->second.getStatValue(stat, false);
				runningStat = static_cast<int>(static_cast<float>(runningStat)* statSet->second.getStatMultiplier(stat));
			}
		}
		//Need to check for stat > limit
		if (runningStat)
		{

		}
		m_effectiveStats.setStatValue(stat, runningStat);

			//m_baseStats.setStatValue(
		//syncStat(static_cast<unsigned int>(stat), static_cast<unsigned int>(mode));
	}
	void StatManagerComponent::syncStat(const unsigned int stat, const StatMode mode)
	{
		syncStat(static_cast<Stat>(stat), mode);
		/*unsigned int prevVal = m_effectiveStats[mode][stat];
		unsigned int statValue = m_baseStats[mode][stat] * (1 + m_baseStatMultipliers[mode][stat]);
		for (auto addVal = m_additionalStatAdders.begin(); addVal != m_additionalStatAdders.end(); ++addVal)
		{
			statValue += addVal->second[mode][stat];
		}
		m_referenceStats[mode][stat] = statValue;

		statValue *= (1 + m_referenceStatMultipliers[mode][stat]);

		for (auto mulVal = m_additionalReferenceStatMultipliers.begin(); mulVal != m_additionalReferenceStatMultipliers.end(); ++mulVal)
		{
			statValue *= mulVal->second[mode][stat];
		}
		//check for stat limits

		auto& limitChecker = m_statLimits[stat];
		int statLimit = limitChecker.getStatLimit();
		if (statValue > statLimit && statLimit != NoStatLimit)
		{
			statValue = statLimit;
		}

		m_effectiveStats[mode][stat] = statValue;
		
		switch (stat)
		{
		case HP:
			m_currentHP[mode] = statValue < m_currentHP[mode] ? statValue : m_currentHP[mode];
			break;
		case MP:
			m_currentMP[mode] = statValue < m_currentMP[mode] ? statValue : m_currentMP[mode];
			break;
		case SP:
			m_currentSP[mode] = statValue < m_currentSP[mode] ? statValue : m_currentSP[mode];
			break;
		}*/
	}

	void StatManagerComponent::syncAllStats()
	{
		for (unsigned int stat = 0; stat < StatCount; ++stat)
		{
			syncStat(static_cast<Stat>(stat));
		}
		/*std::array<int, StatCount> runningStats = m_rawStats.getStats();

		int runningStat = m_rawStats.getStatValue(stat) + static_cast<int>(static_cast<float>(m_permanentStatBoosts.getStatValue(stat, false)) * m_permanentStatBoosts.getStatMultiplier(stat));
		m_baseStats.setStatValue(stat, runningStat);
		runningStat = static_cast<int>(static_cast<float>(runningStat)* m_baseStats.getStatMultiplier(stat));
		for (auto statSetPriority = m_additionalStats.begin(); statSetPriority != m_additionalStats.end(); ++statSetPriority)
		{
			for (auto statSet = statSetPriority->second.begin(); statSet != statSetPriority->second.end(); ++statSet)
			{
				runningStat += statSet->second.getStatValue(stat, false);
				runningStat = static_cast<int>(static_cast<float>(runningStat)* statSet->second.getStatMultiplier(stat));
			}
		}
		//Need to check for stat > limit
		if (runningStat)
		{

		}
		m_effectiveStats.copyStatValues(runningStats);
		m_effectiveStats.setStatValue(stat, runningStat);
		for (unsigned int stat = 0; stat < StatCount; ++stat)
		{
			syncStat(stat);
		}*/
	}

	bool StatManagerComponent::handleStatChangeRequest(ev_ptr statChangeRequestEvent)
	{
		
		switch (statChangeRequestEvent->getEventType())
		{
		case BatchStatChangeRequest::m_eventSignature:
			{
				boost::shared_ptr<BatchStatChangeRequest> batchStatEvent = boost::dynamic_pointer_cast<BatchStatChangeRequest>(statChangeRequestEvent);
				if (ownedBy(batchStatEvent->getChangeTarget()))
				{
					bool valid = false;
					auto& statset = getStatComponent(valid, batchStatEvent->getStatSet());
					if (valid)
					{
						statset.addStatValues(batchStatEvent->getStatChanges());
						syncAllStats();
						return true;
					}
				}
			}
			break;
		case SingleStatChangeRequest::m_eventSignature:
			{
				boost::shared_ptr<SingleStatChangeRequest> singleStatEvent = boost::dynamic_pointer_cast<SingleStatChangeRequest>(statChangeRequestEvent);
				bool valid = false;
				auto& statSet = getStatComponent(valid, singleStatEvent->getStatSet());
				if (valid)
				{
					
				}
			}
			break;
		/*case VolatileStatChangeRequestEvent::m_eventSignature:
			break;
		case StatChangeRequestEvent::m_eventSignature:
			{
				
			}
			break;*/
		}
		return false;
	}
	bool StatManagerComponent::handleNewStatGroupRequest(ev_ptr newStatGroupRequest)
	{
		return false;
	}

	void StatManagerComponent::addStatLimiter(const Stat stat, const int limitLevel, const int limit)
	{
		m_statLimits[limitLevel][static_cast<int>(stat)] = limit;
	}
	void StatManagerComponent::removeStatLimiter(const Stat stat, const int limitLevel, const int limit)
	{

	}
	int StatManagerComponent::getStatLimitLevel(const Stat stat) const
	{
		return m_statLimitLevels[static_cast<int>(stat)];
	}
	int StatManagerComponent::getStatLimitAtLevel(const Stat stat, const int level) const
	{
		auto lv = m_statLimits.find(level);
		if (lv != m_statLimits.end())
		{
			return lv->second[static_cast<int>(stat)];
		}
		return NoStatLimit;
	}
	int StatManagerComponent::getCurrentStatLimit(const Stat stat) const
	{
		int level = m_statLimitLevels[static_cast<int>(stat)];
		auto it = m_statLimits.find(level);
		if (it != m_statLimits.end())
		{
			return it->second[static_cast<int>(stat)];
		}
		return NoStatLimit;
	}
	
	int StatManagerComponent::getStat(bool& validReturn, const Stat stat, const std::string& statGroup)
	{
		auto& sg = getStatComponent(validReturn, statGroup);
		if (validReturn)
		{
			return sg.getStatValue(stat, false);
		}
		return -1;
	}

	void StatManagerComponent::registerEventHandlers(IEventManager* mng)
	{
		m_evMng = mng;
		m_registered = true;
		m_evMng->addListener(fastdelegate::MakeDelegate(this, &StatManagerComponent::handleStatChangeRequest), BatchStatChangeRequest::m_eventSignature);
		m_evMng->addListener(fastdelegate::MakeDelegate(this, &StatManagerComponent::handleStatChangeRequest), SingleStatChangeRequest::m_eventSignature);
		//m_evMng->addListener(fastdelegate::MakeDelegate(this, &StatManagerComponent::handleStatChangeRequest));
	}

	StatComponent& StatManagerComponent::getStatComponent(bool& validReturn, const std::string& statGroup)
	{
		static StatComponent emptyStats(nullptr, -1);
		auto lcGroup = boost::algorithm::to_lower_copy(statGroup);
		//std::string lcGroup(s)
		
		//matchHasher()
		static int rawHash = matchHasher(std::string("raw"));//;// std::string rawStatsString("raw");
		static int permanentHash = matchHasher(std::string("permanent"));
		const int groupHash = matchHasher(lcGroup);

		if (groupHash == rawHash)
		{
			validReturn = true;
			return m_rawStats;
		}
		else if (groupHash == permanentHash)
		{
			validReturn = true;
			return m_permanentStatBoosts;
		}
		else
		{
			auto it = m_additionalStatsByIndex.find(groupHash);
			if (it != m_additionalStatsByIndex.end())
			{
				validReturn = true;
				return *(it->second);
			}
			else
			{
				m_additionalStats[0][lcGroup] = StatComponent(m_owner, -1);
				auto& statSet = m_additionalStats[0][lcGroup];
				m_additionalStatsByIndex[groupHash] = &statSet;
				validReturn = true;
				return statSet;
			}
		}
		validReturn = false;
		return emptyStats;
	}


}