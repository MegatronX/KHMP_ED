#pragma once
#ifndef _ABILITY_MANAGER_H_
#define _ABILITY_MANAGER_H_

#include <map>

#include <components/ActionModifierComponent.h>
#include <abilities/AbilityComponent.h>
#include <entity/Entity.h>

namespace KHMP
{
	class AbilityEntry
	{
	public:
		AbilityEntry(boost::shared_ptr<Entity> abil, AbilityManager& mng)
			: m_learnRate(1.f), m_unlearnable(false), m_alwaysActive(false), m_accumulatedExperience(0), m_level(1), m_learnedInstances(0),
			m_equippedInstances(0), m_ability(abil), m_unlearnedInstances(0), m_abilManager(mng), m_xptoLearn(0)
		{

		}
		bool isAvailable() const
		{
			return (m_learnedInstances + m_unlearnedInstances) > 0;
		}
		unsigned int getAvailableInstances() const
		{
			return m_unlearnedInstances + m_learnedInstances;
		}
		boost::shared_ptr<Entity> getAbility()
		{
			if (m_ability.get() != nullptr)
			{
				auto abilCmp = m_ability->getComponentsAs<AbilityComponent>(AbilityComponent::m_componentType);
				if (abilCmp.size() > 0)
				{
					for (auto abil = abilCmp.begin(); abil != abilCmp.end(); ++abil)
					{
						applyToComponent(*(*abil));
					}
				}
			}
			return m_ability;
		}
		void setUnlearnedInstances(const unsigned int instances);
		void incrementUnlearnedInstances(const unsigned int instances = 1);
		void setLearnedInstances(const unsigned int instances);
		void incrementLearnedInstances(const unsigned int instances = 1);
		void setLevel(const unsigned int level);
		void incrementLevel(const unsigned int level = 1);

		void addXP(unsigned int xp);
		void setLearnRate(const float rate);
		void incrementLearnRate();

		void setLevelingTable(const boost::unordered_map<unsigned int, unsigned int>& lTable);
		void setXpToLearn(const unsigned int xp);
	protected:

		void applyToComponent(AbilityComponent& abilCmp)
		{
			abilCmp.setAvailableInstances(m_unlearnedInstances + m_learnedInstances);
			abilCmp.setEquippedInstances(m_equippedInstances);
			abilCmp.setAbilityLevel(m_level);
		}

		AbilityManager& m_abilManager;
		float m_learnRate;
		bool m_unlearnable;
		bool m_alwaysActive;
		unsigned int m_accumulatedExperience;
		unsigned int m_xptoLearn;
		unsigned int m_level;
		unsigned int m_unlearnedInstances;
		unsigned int m_learnedInstances;
		unsigned int m_equippedInstances;
		boost::unordered_map<unsigned int, unsigned int> m_levelingTable;
		boost::shared_ptr<Entity> m_ability;

	private:

	};
	class AbilityManager : public Component
	{
	public:
		static ComponentType m_componentType;
		AbilityManager(Entity* owner);

		std::multimap<int, Entity*> getAbilitiesActiveOnCallCondition(const CallCondition cc);
		std::multimap<int, ActionModifierComponent*> getActionModifiersWithConditionInOrder(const CallCondition cc);

		void distributeAbilityXP(unsigned int xpgain);

		bool addAbility(boost::shared_ptr<Entity> ability, const unsigned int instances = 1, const float learnRate = 1.f, bool learnedInstance = false);
		bool addAbility(const unsigned int abilID, const unsigned int instances = 1, const float learnRate = 1.f, bool learnedInstance = false);
	protected:
		void handleStatChangeEvent(const ev_ptr evdata);
		void dispatchAbilityAddedEvent(AbilityEntry& ability);

		bool removeAbility(const std::string& abilName);
		bool removeAbility(const unsigned int abilID);
	private:
		boost::unordered_map<std::string, AbilityEntry> m_abilitiesByName;
		boost::unordered_map<unsigned int, AbilityEntry*> m_abiltiiesByID;
		boost::unordered_map<std::string, boost::unordered_map<unsigned int, unsigned int> > m_customLevelingTables;
		boost::unordered_map<std::string, unsigned int> m_customLearningTable;
		std::multimap<CallCondition, AbilityEntry*> m_abilitiesByCallCondition;

		//might want to cache some ability results

		//static AbilityLibrary* m_referenceLibrary;
	};
}

#endif

