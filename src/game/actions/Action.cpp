#include <actions/Action.h>

namespace KHMP
{

	Action::Action(boost::shared_ptr<Entity> owner, ComponentID id, const float acr) : Component(owner, m_componentType, id), m_accuracy(acr), m_isHit(false),
		m_mpCost(0), m_spCost(0), m_hpCost(0)
	{

	}
	Action::Action(Entity& owner, ComponentID id, const float acr) : Component(owner, m_componentType, id), m_accuracy(acr), m_isHit(false),
		m_mpCost(0), m_spCost(0), m_hpCost(0)
	{

	}
	Action::Action(Entity* owner, ComponentID id, const float acr) : Component(owner, m_componentType, id), m_accuracy(acr), m_isHit(false),
		m_mpCost(0), m_spCost(0), m_hpCost(0)
	{

	}

	Action::RawClonePtr Action::rawClone() const
	{
		return RawClonePtr(new Action(*this));
	}

	float Action::getAccuracy() const
	{
		return m_accuracy;
	}
	void Action::setAccuracy(const float acr)
	{
		m_accuracy = acr;
	}

	bool Action::getIsHit() const
	{
		return m_isHit;
	}
	void Action::setIsHit(const bool hit)
	{
		m_isHit = hit;
	}

	ActionGroup& Action::getUsers()
	{
		return m_users;
	}
	ActionGroup& Action::getTargets()
	{
		return m_targets;
	}
	void Action::addUser(Entity& user)
	{
		addUser(ActionTarget(&user, boost::shared_ptr<Entity>()));
	}
	void Action::addTarget(Entity& target)
	{
		addTarget(ActionTarget(&target, boost::shared_ptr<Entity>()));
	}
	void Action::addUser(ActionTarget& user)
	{
		m_users.addMember(user);
	}
	void Action::addTarget(ActionTarget& target)
	{
		m_targets.addMember(target);
	}

	int Action::getMPCost() const
	{
		return m_mpCost;
	}
	int Action::getSPCost() const
	{
		return m_spCost;
	}
	int Action::getHPCost() const
	{
		return m_hpCost;
	}

	void Action::setMPCost(const int mp)
	{
		m_mpCost = mp;
	}
	void Action::setSPCost(const int sp)
	{
		m_spCost = sp;
	}
	void Action::setHPCost(const int hp)
	{
		m_hpCost = hp;
	}

	void Action::pushActionToUsers()
	{
		for (auto user = m_users.getMembers().begin(); user != m_users.getMembers().end(); ++user)
		{
			(*user).second.m_action = this->m_owner->clone();
		}
	}
	void Action::pushActionToTargets()
	{
		for (auto trg = m_targets.getMembers().begin(); trg != m_targets.getMembers().end(); ++trg)
		{
			(*trg).second.m_action = this->m_owner->clone();// cloneAs<Action>();
		}
	}

	void Action::addSubAction(boost::shared_ptr<Entity> action)
	{

	}
	void Action::clearSubActions()
	{
		m_subActions.clear();
	}
	bool Action::hasSubActions() const
	{
		return m_subActions.size() > 0;
	}
	const std::vector<boost::shared_ptr<Entity> >& Action::getSubActions() const
	{
		return m_subActions;
	}
}