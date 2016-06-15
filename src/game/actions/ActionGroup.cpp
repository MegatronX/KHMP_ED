#include <actions/ActionGroup.h>
#include <actions/Action.h>
namespace KHMP
{
	bool ActionGroup::addMember(ActionTarget& member)
	{
		return member.m_originalTarget != nullptr && member.m_action != nullptr && addMember(*(member.m_originalTarget), (member.m_action));
	}
	bool ActionGroup::addMember(Entity& member, boost::shared_ptr<Entity> action)
	{
		auto& memberPair = m_members[member.getEntityName()];
		memberPair.m_originalTarget = &member;
		memberPair.m_finalTarget = &member;
		memberPair.m_action = action;
		//m_members[member.getEntityName()].first = &member;
		///m_members[member.getEntityName()].second = action;// = std::make_pair<Entity*, boost::shared_ptr<Entity> >(&member, action);
		return true;
	}
	bool ActionGroup::addMember(const std::string& name, Entity& member, boost::shared_ptr<Entity> action)
	{
		auto& memberPair = m_members[name];
		memberPair.m_originalTarget = &member;
		memberPair.m_finalTarget = &member;
		memberPair.m_action = action;
		//memberPair.first = &member;
		//memberPair.second = action;
		//m_members[name] = std::make_pair<Entity*, boost::shared_ptr<Entity> >(&member, action);
		return true;
	}

	void ActionGroup::pushActionToAllMembers(Entity* rootAction)
	{
		for (auto member = m_members.begin(); member != m_members.end(); ++member)
		{ 
			member->second.m_action = rootAction->clone();
		}
	}

	void ActionGroup::pushActionToAllMembers(boost::shared_ptr<Entity> action)
	{
		for (auto member = m_members.begin(); member != m_members.end(); ++member)
		{
			member->second.m_action = action->clone();
		}
	}

	boost::unordered_map<std::string, ActionTarget>& ActionGroup::getMembers()
	{
		return m_members;
	}

	
}