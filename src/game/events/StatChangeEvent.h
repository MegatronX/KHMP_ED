#pragma once
#ifndef _STATCHANGEEVENT_H_
#define _STATCHANGEEVENT_H_
#include <events/IEvent.h>
#include <character/Stats.h>
#include <components/StatComponent.h>
class Entity;
namespace KHMP
{
	class BatchStatChangeRequest : public IEvent
	{
	public:
		const static EventType m_eventSignature = 0x2d79e4ee;
		BatchStatChangeRequest(const sf::Time timeStamp, Entity* target);
		BatchStatChangeRequest(const sf::Time timeStamp, StatComponent& stats, Entity* target);
		BatchStatChangeRequest(const sf::Time timeStamp, const std::array<int, StatCount>& changeAdders, Entity* target);
		BatchStatChangeRequest(const sf::Time timeStamp, const std::array<float, StatCount>& statMult, Entity* target);
		BatchStatChangeRequest(const sf::Time timeStamp, const std::array<int, StatCount>& statAdders, const std::array<float, StatCount>& statMults, Entity* target);

		void setStatAdder(const Stat stat, int statAdd);
		void setStatMult(const Stat stat, float statMult);

		int getStatAdder(const Stat stat);
		float getStatMult(const Stat stat);

		const StatComponent& getStatChanges() const;

		const std::string& getStatSet() const;
		void setStatSet(const std::string& targetStats);
		Entity* getChangeTarget() const;
	protected:
		StatComponent m_statChanges;
		std::string m_targetStatSet;
		Entity* m_target;
	};
	class SingleStatChangeRequest : public IEvent
	{
	public:
		SingleStatChangeRequest(const sf::Time timeStamp = sf::Time::Zero);
		const static EventType m_eventSignature = 0xde25d3e9;

		bool targetsVolatileStat() const;

		const std::string& getStatSet() const;
	protected:
	private:
		bool m_volatileStat;
		Stat m_stat;
		int m_statAddChange;
		float m_statMultChange;
		StatMode m_mode;
		std::string m_targetStatSet;
	};

	/*class VolatileStatChangeRequestEvent : public IEvent
	{
	public:
		const static EventType m_eventSignature = ;
		VolatileStatChangeRequestEvent(const sf::Uint32 timeStamp, Stat stat, const int change) : m_stat(stat), m_statChange(change), IEvent(m_eventSignature, timeStamp)
		{

		}
	//protected:
		Stat m_stat;
		bool m_absValue;
		int m_statChange;
	};

	class StatChangeRequestEvent : public IEvent
	{
	public:
		;
		StatChangeRequestEvent(const sf::Uint32 timestamp, const Stat stat, const int statChange, const bool absVal, const bool baseStat = false, const std::string& targetStatSet = std::string());
		StatChangeRequestEvent(const sf::Uint32 timestamp, const Stat stat, const float statChange, const bool absVal, const bool baseStat = false, const std::string& targetStatSet = std::string());
	//protected:
		Stat m_stat;
		int m_statChange;
		float m_statMulChange;
		bool m_absValue;
		bool m_statAdd;
		bool m_statMult;
		bool m_rawStat;
		bool m_permanentStatBoost;
		bool m_referenceStats;
		std::string m_statStorageType;
	};*/

	class StatChangedEvent : public IEvent
	{
	public:
		const static EventType m_eventSignature = 0x8438e286;

		Stat stat;
		int oldValue;
		int newValue;
		bool m_volatile;
	};
}

#endif