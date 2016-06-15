#pragma once
#ifndef _MECHANICS_H_
#define _MECHANICS_H_
#include <ctime>
#include <deque>
#include <vector>

#include <boost/random.hpp>

#include <components/BattleCharacterComponent.h>
#include <actions/Attack.h>
//#include <character/CharacterComponent.h>
class Engine;
namespace KHMP
{
	class BattleField;

	class Mechanics : public Component
	{
	public:
		const static ComponentType m_componentType = 0x1ad5fa0;

		Mechanics(Entity* owner, ComponentID id, Engine* engine, unsigned int RandomSeed = static_cast<unsigned int>(std::time(0)));

		virtual void useAction(Entity& action, BattleField& field);
		virtual void preProcessAction(Entity& action, BattleField& field);
		virtual void processAction(Entity& action, BattleField& field);
		virtual void postProcessAction(Entity& action, BattleField& field);

		virtual bool isCriticalHit(Action& action, Entity& target, BattleField& field);

		virtual bool isCriticalHit(Entity& action, Entity& target, BattleField& field);
		bool isCriticalHit(Entity* action, Entity* target, BattleField& field);
		bool isCriticalHit(boost::shared_ptr<Entity> action, Entity& target, BattleField& field);
		bool isCriticalHit(boost::shared_ptr<Entity> action, boost::shared_ptr<Entity> target, BattleField& field);

		virtual bool isHit(Action& action, Entity& target, BattleField& field);
		virtual bool isHit(Entity& action, Entity& target, BattleField& field);
		bool isHit(Entity* action, Entity* target, BattleField& field);
		bool isHit(boost::shared_ptr<Entity> action, Entity& target, BattleField& field);
		bool isHit(boost::shared_ptr<Entity> action, boost::shared_ptr<Entity> target, BattleField& field);

		virtual int calculateDamage(Action& act, Entity& target, BattleField& field);

		float getElementalDamageMultiplier(Entity& action, Entity& target, BattleField& field) const;
		float getElementalDamageMultiplier(Action& action, Entity& target, BattleField& field) const;
		//float getElementalDamageMultiplier(Action& action, Entity& target, BattleField& field) const;
		float getCriticalDamageMultiplier(Entity& action, Entity& target, BattleField& field) const;
		float getCriticalDamageMultiplier(Attack& action, Entity& target, BattleField& field) const;
		float getPhysicalMagicWeightDamageMultiplier(Entity& action, Entity& target, BattleField& field) const;
		float getPhysicalMagicWeightDamageMultiplier(Attack& action, Entity& target, BattleField& field) const;

		virtual void calculateCost(Action& act, Entity& target, int& mp, int& sp, int& hp);

		virtual void useActionAgainstTarget(Entity& act, Entity& target, BattleField& field);
		virtual void useActionAgainstTarget(Action& act, Entity& target, BattleField& field);
	protected:
		virtual float calculateHitChance(const float mvAcr, const int atkAcr, const int defEv);
	private:
		Engine* m_engine;
		boost::mt19937 m_rngGenerator;
		boost::uniform_real<float> m_0to1RandDistribution;
		boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > m_floatRandGenerator;
		float m_elementalModerator;
		BattleCharacterComponent* m_next;
	};
}

#endif