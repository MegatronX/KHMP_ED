#pragma once
#ifndef _ACTION_H_
#define _ACTION_H_

#include <entity/Entity.h>
#include <actions/ActionGroup.h>
namespace KHMP
{
	class Action : public Component
	{
	public:
		const static ComponentType m_componentType = 0x111d7bc1;
		Action(Entity* owner, ComponentID id, const float acr = 1.f);
		Action(boost::shared_ptr<Entity> owner, ComponentID id, const float acr = 1.f);
		Action(Entity& owner, ComponentID id, const float acr = 1.f);

		virtual RawClonePtr rawClone() const override;

		ActionGroup& getUsers();
		ActionGroup& getTargets();

		bool getIsHit() const;
		void setIsHit(const bool hit);

		float getAccuracy() const;
		void setAccuracy(const float acr);

		void addUser(Entity& user);
		void addTarget(Entity& target);
		void addUser(ActionTarget& user);
		void addTarget(ActionTarget& target);

		int getMPCost() const;
		int getSPCost() const;
		int getHPCost() const;

		void setMPCost(const int mp);
		void setSPCost(const int sp);
		void setHPCost(const int hp);

		void pushActionToUsers();
		void pushActionToTargets();

		void addSubAction(boost::shared_ptr<Entity> action);
		void clearSubActions();
		bool hasSubActions() const;
		bool onlyProcessSubActions() const;
		void setOnlyProcessSubActions(const bool pSub);
		const std::vector<boost::shared_ptr<Entity> >& getSubActions() const;
	protected:
		float m_accuracy;
		bool m_isHit;

		bool m_ignoreUserAbilities;
		bool m_ignoreUserStatusEffects;
		bool m_ignoreTargetAbilities;
		bool m_ignoreTagetStatusEffects;

		ActionGroup m_users;
		ActionGroup m_targets;

		int m_mpCost;
		int m_spCost;
		int m_hpCost;
		bool m_onlyProcessSubActions;
		std::vector<boost::shared_ptr<Entity> > m_subActions;
	private:

	};
}
#endif