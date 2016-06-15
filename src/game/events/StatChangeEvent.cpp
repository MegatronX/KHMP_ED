#include "StatChangeEvent.h"

namespace KHMP
{

	BatchStatChangeRequest::BatchStatChangeRequest(const sf::Time timeStamp, Entity* target) : m_statChanges(nullptr, -1), IEvent(m_eventSignature, timeStamp), m_target(target)
	{

	}
	BatchStatChangeRequest::BatchStatChangeRequest(const sf::Time timeStamp, StatComponent& stats, Entity* target) : m_statChanges(stats), IEvent(m_eventSignature, timeStamp), m_target(target)
	{

	}
	BatchStatChangeRequest::BatchStatChangeRequest(const sf::Time timeStamp, const std::array<int, StatCount>& changeAdders, Entity* target) : m_statChanges(nullptr, -1), IEvent(m_eventSignature, timeStamp), m_target(target)
	{
		m_statChanges.copyStatValues(changeAdders);
	}
	BatchStatChangeRequest::BatchStatChangeRequest(const sf::Time timeStamp, const std::array<float, StatCount>& statMult, Entity* target) : m_statChanges(nullptr, -1), IEvent(m_eventSignature, timeStamp), m_target(target)
	{
		m_statChanges.copyStatMultipliers(statMult);
	}
	BatchStatChangeRequest::BatchStatChangeRequest(const sf::Time timeStamp, const std::array<int, StatCount>& statAdders, const std::array<float, StatCount>& statMults, Entity* target) : m_statChanges(nullptr, -1), IEvent(m_eventSignature, timeStamp), m_target(target)
	{
		m_statChanges.copyStatValues(statAdders);
		m_statChanges.copyStatMultipliers(statMults);
	}

	void BatchStatChangeRequest::setStatAdder(const Stat stat, int statAdd)
	{
		m_statChanges.setStatValue(stat, statAdd);
	}
	void BatchStatChangeRequest::setStatMult(const Stat stat, float statMult)
	{
		m_statChanges.setStatMultiplier(stat, statMult);
	}

	int BatchStatChangeRequest::getStatAdder(const Stat stat)
	{
		return m_statChanges.getStatValue(stat);
	}
	float BatchStatChangeRequest::getStatMult(const Stat stat)
	{
		return m_statChanges.getStatMultiplier(stat);
	}

	const StatComponent& BatchStatChangeRequest::getStatChanges() const
	{
		return m_statChanges;
	}

	const std::string& BatchStatChangeRequest::getStatSet() const
	{
		return m_targetStatSet;
	}
	void BatchStatChangeRequest::setStatSet(const std::string& targetStats)
	{
		m_targetStatSet = targetStats;
	}
	Entity* BatchStatChangeRequest::getChangeTarget() const
	{
		return m_target;
	}
	SingleStatChangeRequest::SingleStatChangeRequest(const sf::Time timeStamp) : IEvent(m_eventSignature, timeStamp)
	{

	}
	//const static EventType m_eventSignature = 0xde25d3e9;

	bool SingleStatChangeRequest::targetsVolatileStat() const
	{
		return m_volatileStat;
	}

	const std::string& SingleStatChangeRequest::getStatSet() const
	{
		return m_targetStatSet;
	}
	
	//const EventType VolatileStatChangeRequestEvent::m_eventSignature = 0x2d79e4ee;// , 0x38da, 0x4e7b, 0x96, 0xc1, 0x43, 0xfd, 0xed, 0x8a, 0x8a, 0x5a);

	//const EventType FixedStatChangeRequestEvent::m_eventSignature = 0xde25d3e9;// 0x9785, 0x4b4e, 0xa4, 0x4e, 0xb2, 0x77, 0x8f, 0xdd, 0x15, 0x70);

	//const EventType CustomStatChangeRequestEvent::m_eventSignature = 0x4f4e01a9;// , 0x1d57, 0x4a8a, 0xb7, 0xf8, 0xf2, 0x26, 0xcc, 0xd0, 0x54, 0x41);

	//const EventType StatChangedEvent::m_eventSignature = 0x8438e286;// , 0xb319, 0x4ccc, 0xa8, 0xd0, 0x22, 0xc1, 0xc8, 0x10, 0xd, 0xda);

	//static EventType m_eventSignature;

	/*StatChangeRequestEvent::StatChangeRequestEvent(const sf::Uint32 timestamp, const Stat stat, const int changeVal, const bool absVal, const bool baseStat, const std::string& targetStatSet) :
		IEvent(m_eventSignature, timestamp), m_stat(stat), m_absValue(absVal), m_statChange(changeVal), m_statAdd(true), m_statMult(false), m_baseStats(baseStat), m_referenceStats(!baseStat), m_statStorageType(targetStatSet)
	{
	}

	StatChangeRequestEvent::StatChangeRequestEvent(const sf::Uint32 timestamp, const Stat stat, const float changeVal, const bool absVal, const bool baseStat, const std::string& targetStatSet) :
		IEvent(m_eventSignature, timestamp), m_stat(stat), m_absValue(absVal), m_statChange(changeVal), m_statAdd(false), m_statMult(true), m_baseStats(baseStat), m_referenceStats(!baseStat), m_statStorageType(targetStatSet)
	{
	}*/
}