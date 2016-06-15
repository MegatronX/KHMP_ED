#pragma once
#ifndef _ABILITYCOMPONENT_H_
#define _ABILITYCOMPONENT_H_

#include <boost/unordered_set.hpp>
#include <battle/CallConditions.h>

#include <component/Component.h>

namespace KHMP
{
	class AbilityComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0xb2c57cab;

		void setAvailableInstances(const unsigned int instances);
		unsigned int getAvailableInstances() const;

		void setEquippedInstances(const unsigned int instances);
		unsigned int getEquippedInstances() const;

		void setAbilityLevel(const unsigned int level);
		unsigned int getAbilityLevel() const;
	protected:
		unsigned int m_availableInstances;
		unsigned int m_equippedInstances;
		unsigned int m_level;
	private:
		boost::unordered_set<CallCondition> m_callConditions;
	};
}

#endif