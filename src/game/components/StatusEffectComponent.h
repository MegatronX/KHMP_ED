#pragma once
#ifndef _STATUSEFFECTCOMPONENT_H_
#define _STATUSEFFECTCOMPONENT_H_

#include <component/Component.h>
#include <boost/unordered_set.hpp>

namespace KHMP
{
	const static int DefaultSETurns = 5;
	class StatusEffectComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0x308ee82e;
		StatusEffectComponent(Entity* owner, const ComponentID& id, const int turns = DefaultSETurns, const int defaultTurns = DefaultSETurns);

		void addReplacement(const std::string& seName);
		void addCancelation(const std::string& seName);

		const boost::unordered_set<std::string>& getReplacementEffects() const;
		const boost::unordered_set<std::string>& getCancellationEffects() const;

		const int getDefaultTurns() const;
		void setDefaultTurns(const int defaultTurns);

		int getRemainingTurns() const;
		void setRemainingTurns(const int turns);

		bool isPositive() const;
		void setIsPositive(const bool positive);

		bool isRefreshable() const;
		void setIsRefreshable(const bool refreshable);

		RawClonePtr rawClone() const;
	protected:
		bool m_positiveEffect;
		int m_defaultTurns;
		int m_turns;
		bool m_refreshable;
		//List of effects that will be removed when this status effect is applied
		boost::unordered_set<std::string> m_replacementEffects;
		//List of status effect that will cancel the application of this status effect and remove that status effect
		boost::unordered_set<std::string> m_cancelEffects;
	};
}

#endif