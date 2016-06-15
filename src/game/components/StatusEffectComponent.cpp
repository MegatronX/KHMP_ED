#include <components/StatusEffectComponent.h>

namespace KHMP
{
	StatusEffectComponent::StatusEffectComponent(Entity* owner, const ComponentID& id, const int turns, const int defaultTurns) : Component(owner, m_componentType, id),
		m_positiveEffect(false), m_defaultTurns(defaultTurns), m_turns(turns), m_refreshable(true)
	{

	}
	void StatusEffectComponent::addReplacement(const std::string& seName)
	{
		m_replacementEffects.insert(seName);
	}
	void StatusEffectComponent::addCancelation(const std::string& seName)
	{
		m_cancelEffects.insert(seName);
	}

	const boost::unordered_set<std::string>& StatusEffectComponent::getReplacementEffects() const
	{
		return m_replacementEffects;
	}
	const boost::unordered_set<std::string>& StatusEffectComponent::getCancellationEffects() const
	{
		return m_cancelEffects;
	}

	const int StatusEffectComponent::getDefaultTurns() const
	{
		return m_defaultTurns;
	}
	void StatusEffectComponent::setDefaultTurns(const int defaultTurns)
	{
		m_defaultTurns = defaultTurns;
	}

	int StatusEffectComponent::getRemainingTurns() const
	{
		return m_turns;
	}
	void StatusEffectComponent::setRemainingTurns(const int turns)
	{
		m_turns = turns;
	}

	bool StatusEffectComponent::isPositive() const
	{
		return m_positiveEffect;
	}
	void StatusEffectComponent::setIsPositive(const bool positive)
	{
		m_positiveEffect = positive;
	}

	bool StatusEffectComponent::isRefreshable() const
	{
		return m_refreshable;
	}
	void StatusEffectComponent::setIsRefreshable(const bool refreshable)
	{
		m_refreshable = refreshable;
	}

	StatusEffectComponent::RawClonePtr StatusEffectComponent::rawClone() const
	{
		return RawClonePtr(new StatusEffectComponent(*this));
	}
}