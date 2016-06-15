#include "Mechanics.h"
#include <engine.h>
#include <boost/make_shared.hpp>

#include <events/IEventManager.h>

#include <entity/Entity.h>
#include <actions/Attack.h>
#include <components/ElementalComponent.h>
#include <components/ActionCostOverride.h>
#include <components/ActionPreprocessComponent.h>
#include <components/IsCriticalHitOverrideComponent.h>
#include <components/IsHitOverrideComponent.h>
#include <components/StatManagerComponent.h>
#include <components/UseActionComponent.h>
#include <components/CalcDamageOverrideComponent.h>
#include <components/MultiActionComponent.h>
#include <battle/BattleField.h>
#include <events/ActionProcessedEvent.h>

namespace KHMP
{
	Mechanics::Mechanics(Entity* owner, ComponentID id, Engine* engine, unsigned int RandomSeed) :
		Component(owner, m_componentType, id), m_elementalModerator(1.f), m_engine(engine), m_rngGenerator(RandomSeed), m_0to1RandDistribution(0.f, 1.f),
		m_floatRandGenerator(m_rngGenerator, m_0to1RandDistribution)
	{
	}

	void Mechanics::useAction(Entity& action, BattleField& field)
	{
		auto multiAction = action.getComponentsAs<MultiActionComponent>(MultiActionComponent::m_componentType);
		if (multiAction.size() > 0)
		{
			for (auto ma = multiAction.begin(); ma != multiAction.end(); ++ma)
			{
				auto subActions = (*ma)->getSubActions();
				for (auto subActionSet = subActions.begin(); subActionSet != subActions.end(); ++subActionSet)
				{
					for (auto subAction = (*subActionSet).second.begin(); subAction != (*subActionSet).second.end(); ++subAction)
					{
						useAction(*(*subAction), field);
					}
				}
			}
		}
		else
		{
			if (0)
			{

			}
			else
			{
				preProcessAction(action, field);
				processAction(action, field);
				postProcessAction(action, field);
			}
		}
	}

	void Mechanics::preProcessAction(Entity& action, BattleField& field)
	{
		auto ppsAction = action.getComponentsAs<ActionPreprocessComponent>(ActionPreprocessComponent::m_componentType);
		auto actionCmps = action.getComponentsAs<Action>(Action::m_componentType);
		for (auto actCmp = actionCmps.begin(); actCmp != actionCmps.end(); ++actCmp)
		{
			auto users = (*actCmp)->getUsers();
			auto targets = (*actCmp)->getTargets();
			for (auto user = users.getMembers().begin(); user != users.getMembers().end(); ++user)
			{
				if ((*user).second.m_originalTarget)
					auto usrCmps = (*user).second.m_originalTarget->getComponentsAs<ActionPreprocessComponent>(ActionPreprocessComponent::m_componentType);
			}
		}
		//auto ppsusers
	}
	void Mechanics::processAction(Entity& action, BattleField& field)
	{
		if (0)
		{

		}
		else //default handling of action
		{
			auto actCmps = action.getComponentsAs<Action>(Action::m_componentType);
			if (actCmps.size() > 0)
			{
				for (auto actCmp = actCmps.begin(); actCmp != actCmps.end(); ++actCmp)
				{
					(*actCmp)->pushActionToTargets();
					(*actCmp)->pushActionToUsers();
					auto targets = (*actCmp)->getTargets();
					for (auto target = targets.getMembers().begin(); target != targets.getMembers().end(); ++target)
					{
						if ((target->second.m_action))
							useActionAgainstTarget(*(target->second.m_action), *(target->second.m_finalTarget), field);
					}
					/*if (!(*action)->hasSubActions() || !((*action)->onlyProcessSubActions()))
					{
						(*action)->pushActionToTargets();
						(*action)->pushActionToUsers();
						auto targets = (*action)->getTargets();
						for (auto target = targets.getMembers().begin(); target != targets.getMembers().end(); ++target)
						{
							useActionAgainstTarget(*(target->second.second), *(target->second.first), field);
						}
					}
					if ((*action)->hasSubActions())
					{
						for (auto subAct = (*action)->getSubActions().begin(); subAct != (*action)->getSubActions().end(); ++subAct)
						{
							processAction(*(*subAct), field);
						}
					}*/
				}
			}
		}
	}
	void Mechanics::postProcessAction(Entity& action, BattleField& field)
	{

	}

	bool Mechanics::isHit(Action& action, Entity& target, BattleField& field)
	{
		bool hit = false;
		bool set = false;
		if ((action.hasFlag("AlwaysHits") || action.hasFlag("AlwaysHit") || action.hasFlag("PerfectAccuracy")) && !(target.hasFlag("Unhittable") || target.hasFlag("PerfectEvasion")))
		{
			hit = true;
		}
		else if (target.hasFlag("Unhittable") || target.hasFlag("PerfectEvasion"))
		{
			hit = false;
		}
		else
		{
			auto overrides = action.getOwner()->getComponentsAs<IsHitOverrideComponent>(IsHitOverrideComponent::m_componentType);
			std::vector<IsHitOverrideComponent*> attackerOverrides;
			auto defenderOverrides = target.getComponentsAs<IsHitOverrideComponent>(IsHitOverrideComponent::m_componentType);
			if (overrides.size() > 0 || attackerOverrides.size() > 0 || defenderOverrides.size() > 0)
			{
				std::vector<IsHitOverrideComponent*> allOverrides;//
				allOverrides.reserve(overrides.size() + defenderOverrides.size());
				allOverrides.insert(allOverrides.end(), overrides.begin(), overrides.end());
				allOverrides.insert(allOverrides.end(), defenderOverrides.begin(), defenderOverrides.end());
				allOverrides.insert(allOverrides.end(), attackerOverrides.begin(), attackerOverrides.end());
				std::sort(allOverrides.begin(), allOverrides.end(),
					[](const IsHitOverrideComponent* a, const IsHitOverrideComponent* b) -> bool
				{
					return a->getPriority() > b->getPriority();
				});
				for (auto hitOverride = allOverrides.begin(); hitOverride != allOverrides.end(); ++hitOverride)
				{
					hit = (*hitOverride)->isHit(action, target, field, hit);
				}
				action.setIsHit(hit);
				/*auto actionCmps = action.getComponentsAs<Action>(Action::m_componentType);
				if (actionCmps.size() > 0)
				{
				for (auto actCmp = actionCmps.begin(); actCmp != actionCmps.end(); ++actCmp)
				{
				for (auto hitOverride = allOverrides.begin(); hitOverride != allOverrides.end(); ++hitOverride)
				{
				hit = (*hitOverride)->isHit(*(*actCmp), target, field, hit);
				}
				(*actCmp)->setIsHit(hit);
				}
				}*/
			}
			else
			{
				int avgUserAcr = 0;
				int acrAdds = 0;
				auto& defSMs = target.getComponentsAs<StatManagerComponent>(StatManagerComponent::m_componentType);
				int defenderAvgEvasion = 0;
				int defenderAvgMgEvasion = 0;
				if (defSMs.size() > 0)
				{
					for (auto sm = defSMs.begin(); sm != defSMs.end(); ++sm)
					{
						bool validEv = true;
						bool validMgEv = true;

						int tempEv = (*sm)->getStat(validEv, Stat::Evasion);
						if (validEv)
							defenderAvgEvasion += tempEv;
						int tempMgEv = (*sm)->getStat(validMgEv, Stat::MgEvasion);
						if (validMgEv)
							defenderAvgMgEvasion += tempMgEv;

					}
					defenderAvgEvasion /= defSMs.size();
					defenderAvgMgEvasion /= defSMs.size();
				}
				int userAvgAccuracy = 0;
				int userAvgMgAccuracy = 0;
				int adds = 0;
				auto& users = action.getUsers();
				auto& rawUsers = users.getMembers();
				auto atkCmp = dynamic_cast<Attack*>(&action);
				for (auto user = rawUsers.begin(); user != rawUsers.end(); ++user)
				{
					auto& sms = user->second.m_finalTarget->getComponentsAs<StatManagerComponent>(StatManagerComponent::m_componentType);
					for (auto sm = sms.begin(); sm != sms.end(); ++sm)
					{
						bool validAcr = true;
						bool validMgAcr = true;
						int tempAcr = (*sm)->getStat(validAcr, Stat::Accuracy);
						if (validAcr)
							userAvgAccuracy += tempAcr;
						int tempMgAcr = (*sm)->getStat(validMgAcr, Stat::MgAccuracy);
						if (validMgAcr)
							userAvgMgAccuracy += tempMgAcr;
						if (validAcr || validMgAcr)
							++adds;
					}
				}
				if (adds > 0)
				{
					userAvgAccuracy /= adds;
					userAvgMgAccuracy /= adds;
				}
				float mvAcr = action.getAccuracy();
				float atkActMod = 1.f;
				float hitChance = 1.f;
				if (atkCmp)
				{
					hitChance = atkCmp->getPhysicalWeight() * calculateHitChance(mvAcr, userAvgAccuracy, defenderAvgEvasion) +
						atkCmp->getMagicWeight() * calculateHitChance(mvAcr, userAvgMgAccuracy, defenderAvgMgEvasion);
				}
				else
				{
					hitChance = 1.f; //may need to modify this
				}
				hit = hitChance > m_floatRandGenerator();
				action.setIsHit(hit);
			}
		}
		return hit;
	}

	bool Mechanics::isHit(Entity& action, Entity& target, BattleField& field)
	{
		bool hit = false;
		bool set = false;
		if ((action.hasFlag("AlwaysHits") || action.hasFlag("AlwaysHit") || action.hasFlag("PerfectAccuracy")) && !(target.hasFlag("Unhittable") || target.hasFlag("PerfectEvasion")))
		{
			hit = true;
		}
		else if (target.hasFlag("Unhittable") || target.hasFlag("PerfectEvasion"))
		{
			hit = false;
		}
		else
		{
			auto overrides = action.getComponentsAs<IsHitOverrideComponent>(IsHitOverrideComponent::m_componentType);
			std::vector<IsHitOverrideComponent*> attackerOverrides;
			auto defenderOverrides = target.getComponentsAs<IsHitOverrideComponent>(IsHitOverrideComponent::m_componentType);
			if (overrides.size() > 0 || attackerOverrides.size() > 0 || defenderOverrides.size() > 0)
			{
				std::vector<IsHitOverrideComponent*> allOverrides;//
				allOverrides.reserve(overrides.size() + defenderOverrides.size());
				allOverrides.insert(allOverrides.end(), overrides.begin(), overrides.end());
				allOverrides.insert(allOverrides.end(), defenderOverrides.begin(), defenderOverrides.end());
				allOverrides.insert(allOverrides.end(), attackerOverrides.begin(), attackerOverrides.end());
				std::sort(allOverrides.begin(), allOverrides.end(),
					[](const IsHitOverrideComponent* a, const IsHitOverrideComponent* b) -> bool
				{
					return a->getPriority() > b->getPriority();
				});
				auto actionCmps = action.getComponentsAs<Action>(Action::m_componentType);
				if (actionCmps.size() > 0)
				{
					for (auto actCmp = actionCmps.begin(); actCmp != actionCmps.end(); ++actCmp)
					{
						if ((*actCmp)->hasFlag("AlwaysHits") || (*actCmp)->hasFlag("AlwaysHit") || (*actCmp)->hasFlag("PerfectAccuracy"))
							hit = true;
						else
						{
							for (auto hitOverride = allOverrides.begin(); hitOverride != allOverrides.end(); ++hitOverride)
							{
								hit = (*hitOverride)->isHit(*(*actCmp), target, field, hit);
							}
						}
						(*actCmp)->setIsHit(hit);
					}
				}
			}
			else //no overrides, do normal hit calcualtion
			{
				float hitChance = 1.f;
				auto actionCmps = action.getComponentsAs<Action>(Action::m_componentType);
				if (actionCmps.size() > 0)
				{
					int avgUserAcr = 0;
					int acrAdds = 0;
					auto& defSMs = target.getComponentsAs<StatManagerComponent>(StatManagerComponent::m_componentType);
					int defenderAvgEvasion = 0;
					int defenderAvgMgEvasion = 0;
					if (defSMs.size() > 0)
					{
						for (auto sm = defSMs.begin(); sm != defSMs.end(); ++sm)
						{
							bool validEv = true;
							bool validMgEv = true;

							int tempEv = (*sm)->getStat(validEv, Stat::Evasion);
							if (validEv)
								defenderAvgEvasion += tempEv;
							int tempMgEv = (*sm)->getStat(validMgEv, Stat::MgEvasion);
							if (validMgEv)
								defenderAvgMgEvasion += tempMgEv;

						}
						defenderAvgEvasion /= defSMs.size();
						defenderAvgMgEvasion /= defSMs.size();
					}
					for (auto actCmp = actionCmps.begin(); actCmp != actionCmps.end(); ++actCmp)
					{
						if ((*actCmp)->hasFlag("AlwaysHits") || (*actCmp)->hasFlag("AlwaysHit") || (*actCmp)->hasFlag("PerfectAccuracy"))
						{
							(*actCmp)->setIsHit(true);
							set = true;
						}
						else if ((*actCmp)->hasFlag("NeverCritical"))
						{
							(*actCmp)->setIsHit(false);
							set = true;
						}
						else
						{
							int userAvgAccuracy = 0;
							int userAvgMgAccuracy = 0;
							int adds = 0;
							auto& users = (*actCmp)->getUsers();
							auto& rawUsers = users.getMembers();
							auto atkCmp = dynamic_cast<Attack*>(*actCmp);
							for (auto user = rawUsers.begin(); user != rawUsers.end(); ++user)
							{
								auto& sms = user->second.m_finalTarget->getComponentsAs<StatManagerComponent>(StatManagerComponent::m_componentType);
								for (auto sm = sms.begin(); sm != sms.end(); ++sm)
								{
									bool validAcr = true;
									bool validMgAcr = true;
									int tempAcr = (*sm)->getStat(validAcr, Stat::Accuracy);
									if (validAcr)
										userAvgAccuracy += tempAcr;
									int tempMgAcr = (*sm)->getStat(validMgAcr, Stat::MgAccuracy);
									if (validMgAcr)
										userAvgMgAccuracy += tempMgAcr;
									if (validAcr || validMgAcr)
										++adds;
								}
							}
							if (adds > 0)
							{
								userAvgAccuracy /= adds;
								userAvgMgAccuracy /= adds;
							}
							float mvAcr = (*actCmp)->getAccuracy();
							float atkActMod = 1.f;
							if (atkCmp)
							{
								hitChance = atkCmp->getPhysicalWeight() * calculateHitChance(mvAcr, userAvgAccuracy, defenderAvgEvasion) +
									atkCmp->getMagicWeight() * calculateHitChance(mvAcr, userAvgMgAccuracy, defenderAvgMgEvasion);
							}
							else
							{
								hitChance = 1.f; //may need to modify this
							}
							hit = hitChance > m_floatRandGenerator();
							(*actCmp)->setIsHit(hit);
							set = true;
							/*for (auto atkCmp = actionCmps.begin(); atkCmp != actionCmps.end(); ++atkCmp)
							{
								(*atkCmp)->setIsHit(hit);
							}*/
						}
					}
				}
			}
		}
		if (!set)
		{
			auto attackCmps = action.getComponentsAs<Attack>(Attack::m_componentType);
			if (attackCmps.size() > 0)
			{
				for (auto atkCmp = attackCmps.begin(); atkCmp != attackCmps.end(); ++atkCmp)
				{
					(*atkCmp)->setIsHit(hit);
				}
			}
		}
		return hit;
	}
	bool Mechanics::isHit(Entity* action, Entity* target, BattleField& field)
	{
		return action != nullptr && target != nullptr && isHit(*action, *target, field);
	}
	bool Mechanics::isHit(boost::shared_ptr<Entity> action, Entity& target, BattleField& field)
	{
		return action.get() != nullptr && isHit(*action, target, field);
	}

	bool Mechanics::isCriticalHit(Action& action, Entity& target, BattleField& field)
	{
		bool critical = false;
		if ((action.hasFlag("AlwaysCritical") || action.hasFlag("AlwaysCrit")) && !(target.hasFlag("Uncritable")))
		{
			critical = true;
		}
		else if (target.hasFlag("Uncritiable") || ((action.hasFlag("NeverCritical") || action.hasFlag("NeverCrit")) && !(target.hasFlag("AlwaysCritable") || action.hasFlag("FixedDamage"))))
		{
			critical = false;
		}
		else
		{
			Attack* atk = dynamic_cast<Attack*>(&action);
			if (atk)
			{
				if (atk->hasProperty("AlwaysCritical") || action.hasFlag("AlwaysCrit"))
				{
					critical = true;
					atk->setIsCritical(critical);
				}
				else
				{
					auto overrides = action.getOwner()->getComponentsAs<IsCriticalHitOverrideComponent>(IsCriticalHitOverrideComponent::m_componentType);
					std::vector<IsCriticalHitOverrideComponent*> userOverrides;
					for (auto user = action.getUsers().getMembers().begin(); user != action.getUsers().getMembers().end(); ++user)
					{
						auto or = (*user).second.m_finalTarget->getComponentsAs<IsCriticalHitOverrideComponent>(IsCriticalHitOverrideComponent::m_componentType);
						userOverrides.insert(userOverrides.end(), or.begin(), or.end());
					}
					auto defenderOverrides = target.getComponentsAs<IsCriticalHitOverrideComponent>(IsCriticalHitOverrideComponent::m_componentType);
					if (overrides.size() > 0 || userOverrides.size() > 0 || defenderOverrides.size() > 0)
					{
						std::vector<IsCriticalHitOverrideComponent*> allOverrides;//
						allOverrides.reserve(overrides.size() + userOverrides.size() + defenderOverrides.size());
						allOverrides.insert(allOverrides.end(), overrides.begin(), overrides.end());
						allOverrides.insert(allOverrides.end(), defenderOverrides.begin(), defenderOverrides.end());
						allOverrides.insert(allOverrides.end(), userOverrides.begin(), userOverrides.end());
						std::sort(allOverrides.begin(), allOverrides.end(),
							[](const IsCriticalHitOverrideComponent* a, const IsCriticalHitOverrideComponent* b) -> bool
						{
							return a->getPriority() > b->getPriority();
						});
						for (auto critOverride = allOverrides.begin(); critOverride != allOverrides.end(); ++critOverride)
						{
							critical = (*critOverride)->isCriticalHit(*atk, target, field, critical);
						}
						atk->setIsCritical(critical);
					}
					else
					{
						critical = atk->getCriticalChance() > m_floatRandGenerator();// critChance > m_floatRandGenerator();
						atk->setIsCritical(critical);
					}
				}
			}
		}
		return critical;
	}

	bool Mechanics::isCriticalHit(boost::shared_ptr<Entity> action, boost::shared_ptr<Entity> target, BattleField& field)
	{
		return isCriticalHit(action.get(), target.get(), field);
	}
	bool Mechanics::isCriticalHit(Entity& action, Entity& target, BattleField& field)
	{
		bool critical = false;
		bool set = false;
		if ((action.hasFlag("AlwaysCritical") || action.hasFlag("AlwaysCrit")) && !(target.hasFlag("Uncritable")))
		{
			critical = true;
		}
		else if ((action.hasFlag("NeverCritical") || action.hasFlag("NeverCrit")) && !(target.hasFlag("AlwaysCritable")))
		{
			critical = false;
		}
		else
		{
			auto overrides = action.getComponentsAs<IsCriticalHitOverrideComponent>(IsCriticalHitOverrideComponent::m_componentType);
			auto defenderOverrides = target.getComponentsAs<IsCriticalHitOverrideComponent>(IsCriticalHitOverrideComponent::m_componentType);
			if (overrides.size() > 0 || defenderOverrides.size() > 0)
			{
				std::vector<IsCriticalHitOverrideComponent*> allOverrides;//
				allOverrides.reserve(overrides.size() + defenderOverrides.size());
				allOverrides.insert(allOverrides.end(), overrides.begin(), overrides.end());
				allOverrides.insert(allOverrides.end(), defenderOverrides.begin(), defenderOverrides.end());
				std::sort(allOverrides.begin(), allOverrides.end(), 
					[](const IsCriticalHitOverrideComponent* a, const IsCriticalHitOverrideComponent* b) -> bool
				{
					return a->getPriority() > b->getPriority();
				});
				auto attackCmps = action.getComponentsAs<Attack>(Attack::m_componentType);
				for (auto atkCmp = attackCmps.begin(); atkCmp != attackCmps.end(); ++atkCmp)
				{
					for (auto critOverride = allOverrides.begin(); critOverride != allOverrides.end(); ++critOverride)
					{
						critical = (*critOverride)->isCriticalHit(*(*atkCmp), target, field, critical);
					}
					(*atkCmp)->setIsCritical(critical);
				}
			}
			else //no overrides, do normal critical calcualtion
			{
				float critChance = 0.f;
				auto attackCmps = action.getComponentsAs<Attack>(Attack::m_componentType);
				if (attackCmps.size() > 0)
				{
					for (auto atkCmp = attackCmps.begin(); atkCmp != attackCmps.end(); ++atkCmp)
					{
						critical = (*atkCmp)->getCriticalChance() > m_floatRandGenerator();// critChance > m_floatRandGenerator();
						(*atkCmp)->setIsCritical(critical);
					}
					set = true;
				}
			}
			
		}
		/*if (!set)
		{
			auto attackCmps = action.getComponentsAs<Attack>(Attack::m_componentType);
			if (attackCmps.size() > 0)
			{
				for (auto atkCmp = attackCmps.begin(); atkCmp != attackCmps.end(); ++atkCmp)
				{
					(*atkCmp)->setIsCritical(critical);
				}
			}
		}*/
		//auto critCmps = 
		return critical;
	}
	bool Mechanics::isCriticalHit(Entity* action, Entity* target, BattleField& field)
	{
		return action != nullptr && target != nullptr && isCriticalHit(*action, *target, field);
	}
	bool Mechanics::isCriticalHit(boost::shared_ptr<Entity> action, Entity& target, BattleField& field)
	{
		return action.get() != nullptr && isCriticalHit(*action, target, field);
	}

	/*bool Mechanics::isCriticalHit(boost::shared_ptr<Entity> action, boost::shared_ptr<Entity> target, BattleField& field)
	{
		return isCriticalHit(action.get(), target.get(), field);
	}*/

	int Mechanics::calculateDamage(Action& act, Entity& target, BattleField& field)
	{
		int damage = 0;
		auto atk = dynamic_cast<Attack*>(&act);
		if (atk)
		{
			if (atk->hasProperty("FixedDamage"))
			{
				auto& dmgStr = atk->getProperty("FixedDamageAmount");
				damage = boost::lexical_cast<int>(dmgStr);
			}
			else
			{
				//find dmg overrides
				
			}
		}
		return damage;
	}

	float Mechanics::getElementalDamageMultiplier(Entity& action, Entity& target, BattleField& field) const
	{
		float multiplier = 1.f;
		//check for action override of this 
		/*
		auto dmgoverrides = action.getComponentsAs<ElementalDamageMultiplierComponent>(ElementalDamageMultiplierComponent::m_componentType);
		if (dmgoverrides.size() > 0)
		{
		}
		else
		{
		*/
		if (!(action.hasFlag("IgnoreElements") || action.hasFlag("IgnoreElementalDamage")))
		{
			auto eleWeights = action.getComponentsAs<ElementalComponent>(ElementalComponent::m_componentType);
			auto defenderWeights = action.getComponentsAs<ElementalComponent>(ElementalComponent::m_componentType);
			if (eleWeights.size() > 0 && defenderWeights.size() > 0)
			{
				boost::unordered_map<Elements::Element, float> attackWeights;
				for (auto eleCmp = eleWeights.begin(); eleCmp != eleWeights.end(); ++eleCmp)
				{
					if ((*eleCmp)->hasAnyElementAvailable())
					{
						auto& localWeights = (*eleCmp)->getElementWeights();
						for (auto localEle = localWeights.begin(); localEle != localWeights.end(); ++localEle)
						{
							attackWeights[localEle->first] += (*eleCmp)->getElementalWeight(localEle->first);// localEle->second;
						}
					}
				}
				if (attackWeights.size() > 0)
				{
					for (auto attackerEle = attackWeights.begin(); attackerEle != attackWeights.end(); ++attackerEle)
					{
						for (auto defCmp = defenderWeights.begin(); defCmp != defenderWeights.end(); ++defCmp)
						{
							if ((*defCmp)->hasElementAvailable(attackerEle->first))
							{
								multiplier += (attackerEle->second * ((*defCmp)->getElementalWeight(attackerEle->first) - m_elementalModerator));
							}
						}
					}
				}
			}
		}
		/*
		}
		*/
		return multiplier;
	}
	float Mechanics::getElementalDamageMultiplier(Action& action, Entity& target, BattleField& field) const
	{
		float multiplier = 1.f;
		//check for action override of this 
		/*
		auto dmgoverrides = action.getComponentsAs<ElementalDamageMultiplierComponent>(ElementalDamageMultiplierComponent::m_componentType);
		if (dmgoverrides.size() > 0)
		{
		}
		else
		{
		*/
		/*if (!(action.hasFlag("IgnoreElements") || action.hasFlag("IgnoreElementalDamage")))
		{
			auto eleWeights = action.getComponentsAs<ElementalComponent>(ElementalComponent::m_componentType);
			auto defenderWeights = action.getComponentsAs<ElementalComponent>(ElementalComponent::m_componentType);
			if (eleWeights.size() > 0 && defenderWeights.size() > 0)
			{
				boost::unordered_map<Elements::Element, float> attackWeights;
				for (auto eleCmp = eleWeights.begin(); eleCmp != eleWeights.end(); ++eleCmp)
				{
					if ((*eleCmp)->hasAnyElementAvailable())
					{
						auto& localWeights = (*eleCmp)->getElementWeights();
						for (auto localEle = localWeights.begin(); localEle != localWeights.end(); ++localEle)
						{
							attackWeights[localEle->first] += (*eleCmp)->getElementalWeight(localEle->first);// localEle->second;
						}
					}
				}
				if (attackWeights.size() > 0)
				{
					for (auto attackerEle = attackWeights.begin(); attackerEle != attackWeights.end(); ++attackerEle)
					{
						for (auto defCmp = defenderWeights.begin(); defCmp != defenderWeights.end(); ++defCmp)
						{
							if ((*defCmp)->hasElementAvailable(attackerEle->first))
							{
								multiplier += (attackerEle->second * ((*defCmp)->getElementalWeight(attackerEle->first) - m_elementalModerator));
							}
						}
					}
				}
			}
		}*/
		/*
		}
		*/
		return multiplier;
	}
	float Mechanics::getCriticalDamageMultiplier(Entity& action, Entity& target, BattleField& field) const
	{
		float multiplier = 1.f;
		if (0)
		{

		}
		else
		{
			
		}
		return multiplier;
	}

	float Mechanics::getCriticalDamageMultiplier(Attack& action, Entity& target, BattleField& field) const
	{
		float multiplier = 1.f;
		if (0)
		{

		}
		else
		{

		}
		return multiplier;
	}

	float Mechanics::getPhysicalMagicWeightDamageMultiplier(Entity& action, Entity& target, BattleField& field) const
	{
		float multiplier = 1.f;
		if (0)
		{

		}
		else
		{

		}
		return multiplier;
	}

	float Mechanics::getPhysicalMagicWeightDamageMultiplier(Attack& action, Entity& target, BattleField& field) const
	{
		float multiplier = 1.f;
		if (0)
		{

		}
		else
		{

		}
		return multiplier;
	}
	/*float Mechanics::getElementalDamageMultiplier(Action& action, Entity& target, BattleField& field) const
	{
		float multiplier = 1.f;
		if (!(action.getOwner()->hasFlag("IgnoreElements") || action.getOwner()->hasFlag("IgnoreElementalDamage")))
		{
			auto eleWeights = action.getOwner()->getComponentsAs<ElementalComponent>(ElementalComponent::m_componentType);
			auto defenderWeights = action.getOwner()->getComponentsAs<ElementalComponent>(ElementalComponent::m_componentType);
			if (eleWeights.size() > 0 && defenderWeights.size() > 0)
			{
				boost::unordered_map<Elements::Element, float> attackWeights;
				for (auto eleCmp = eleWeights.begin(); eleCmp != eleWeights.end(); ++eleCmp)
				{
					if ((*eleCmp)->hasAnyElementAvailable())
					{
						auto& localWeights = (*eleCmp)->getElementWeights();
						for (auto localEle = localWeights.begin(); localEle != localWeights.end(); ++localEle)
						{
							attackWeights[localEle->first] += (*eleCmp)->getElementalWeight(localEle->first);// localEle->second;
						}
					}
				}
				if (attackWeights.size() > 0)
				{
					for (auto attackerEle = attackWeights.begin(); attackerEle != attackWeights.end(); ++attackerEle)
					{
						for (auto defCmp = defenderWeights.begin(); defCmp != defenderWeights.end(); ++defCmp)
						{
							if ((*defCmp)->hasElementAvailable(attackerEle->first))
							{
								multiplier += (attackerEle->second * ((*defCmp)->getElementalWeight(attackerEle->first) - m_elementalModerator));
							}
						}
					}
				}
			}
		}
		return multiplier;
	}*/

	float Mechanics::calculateHitChance(const float mvAcr, const int atkAcr, const int defEv)
	{
		float defEvEffective = defEv <= 0 ? 1.f : (defEv << 1);
		float chance = mvAcr * (1.f + (static_cast<float>(atkAcr) / defEvEffective));
		return chance;
	}

	void Mechanics::calculateCost(Action& act, Entity& target, int& mp, int& sp, int& hp)
	{
		mp = 0;
		sp = 0;
		hp = 0;
		auto costOverrides = act.getOwner()->getComponentsAs<ActionCostOverride>(ActionCostOverride::m_componentType);
		auto defCostOverrides = target.getComponentsAs<ActionCostOverride>(ActionCostOverride::m_componentType);
		if (costOverrides.size() > 0 || defCostOverrides.size())
		{
			std::vector<ActionCostOverride*> allOverrides;//
			allOverrides.reserve(costOverrides.size() + defCostOverrides.size());
			allOverrides.insert(allOverrides.end(), costOverrides.begin(), costOverrides.end());
			allOverrides.insert(allOverrides.end(), defCostOverrides.begin(), defCostOverrides.end());
			std::sort(allOverrides.begin(), allOverrides.end(),
				[](const ActionCostOverride* a, const ActionCostOverride* b) -> bool
			{
				return a->getPriority() > b->getPriority();
			});
			for (auto costOverride = allOverrides.begin(); costOverride != allOverrides.begin(); ++costOverride)
			{
				(*costOverride)->calculateCost(act, target, mp, sp, hp);
			}
			act.setHPCost(hp);
			act.setMPCost(mp);
			act.setSPCost(sp);
		}
		else
		{
			mp = act.getMPCost();
			sp = act.getSPCost();
			hp = act.getHPCost();
		}
	}

	void Mechanics::useActionAgainstTarget(Entity& action, Entity& target, BattleField& field)
	{
		auto useCmps = action.getComponentsAs<UseActionAgainstTargetComponent>(UseActionAgainstTargetComponent::m_componentType);
		if (useCmps.size() > 0)
		{

		}
		else
		{
			auto actCmps = action.getComponentsAs<Action>(Action::m_componentType);
			if (actCmps.size() > 0)
			{
				isHit(action, target, field);
				isCriticalHit(action, target, field);
				for (auto act = actCmps.begin(); act != actCmps.end(); ++act)
				{
					Attack* atk = dynamic_cast<Attack*>(*act);
					
					if ((*act)->getIsHit())
					{
						
						if (atk)
						{
							float critMultiplier = 1.f;
							float elementalMultiplier = getElementalDamageMultiplier(action, target, field);
							float weightedMultipler = getPhysicalMagicWeightDamageMultiplier(action, target, field);
							if (atk->getIsCritical())
								critMultiplier = getCriticalDamageMultiplier(action, target, field);
							float totalMultiplier = critMultiplier * weightedMultipler * elementalMultiplier;
							atk->setFinalPower(atk->getBasePower() * totalMultiplier);
							//critMultiplier = 
						}
						int mpcost = 0;
						int spcost = 0;
						int hpcost = 0;
						calculateCost(*(*act), target, mpcost, spcost, hpcost);
						int dmg = calculateDamage(*(*act), target, field);
						atk->setCalculatedDamage(dmg);
						//Fire off action processed event
					}
					if (m_engine)
					{
						auto actPEvent = boost::make_shared<ActionProcessedEvent>(*act, &target, &field, this);
						auto ev = m_engine->getEventManager().triggerEvent(actPEvent);
						/*if (ev)
						{
							ev->triggerEvent(actPEvent);
						}*/
					}
				}
			}
			/*if (actCmps.size())
			{

			}
			if (isHit(act, target, field))
			{
				auto actCmps = act.getComponentsAs<Action>(Action::m_componentType);
				if (actCmps.size())
				{
					float eleDmgMult = getElementalDamageMultiplier(act, target, field);
					float critMult = 1.f;
					if (isCriticalHit(act, target, field))
					{
						critMult = getCriticalDamageMultiplier(act, target, field);
					}
					float physMagWeightMul = getPhysicalMagicWeightDamageMultiplier(act, target, field);
					float totalMultiplier = eleDmgMult * critMult * physMagWeightMul;
					for (auto act = actCmps.begin(); act != actCmps.end(); ++act)
					{
						auto atk = dynamic_cast<Attack*>(*act);
						if (atk)
						{
							atk->setFinalPower(atk->getBasePower() * totalMultiplier);
						}
						int mpcost = 0;
						int spcost = 0;
						int hpcost = 0;
						calculateCost(*(*act), target, mpcost, spcost, hpcost);
						int dmg = calculateDamage(*(*act), target, field);
						//fire off damage request event

					}

				}
			}*/
		}
	}
	void Mechanics::useActionAgainstTarget(Action& act, Entity& target, BattleField& field)
	{
		bool hit = isHit(act, target, field);
		Attack* atk = dynamic_cast<Attack*>(&act);
		if (hit)
		{
			if (atk)
			{
				isCriticalHit(act, target, field);
				float critMultiplier = 1.f;
				float elementalMultiplier = getElementalDamageMultiplier(act, target, field);
				float weightedMultipler = getPhysicalMagicWeightDamageMultiplier(*atk, target, field);
				if (atk->getIsCritical())
					critMultiplier = getCriticalDamageMultiplier(*atk, target, field);
				float totalMultiplier = critMultiplier * weightedMultipler * elementalMultiplier;
				atk->setFinalPower(atk->getBasePower() * totalMultiplier);
			}
			int mpcost = 0;
			int spcost = 0;
			int hpcost = 0;
			calculateCost(act, target, mpcost, spcost, hpcost);
			int dmg = calculateDamage(act, target, field);
			atk->setCalculatedDamage(dmg);
		}
		if (m_engine)
		{
			auto actPEvent = boost::make_shared<ActionProcessedEvent>(&act, &target, &field, this);
			auto ev = m_engine->getEventManager().triggerEvent(actPEvent);
			/*if (ev)
			{
			ev->triggerEvent(actPEvent);
			}*/
		}
	}
}