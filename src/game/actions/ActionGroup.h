#pragma once
#ifndef _ACTIONGROUP_H_
#define _ACTIONGROUP_H_

#include <boost/unordered_map.hpp>

#include <entity/Entity.h>
#include <utility>

namespace KHMP
{
	class Action;
	struct ActionTarget
	{
		ActionTarget() : m_originalTarget(nullptr), m_finalTarget(nullptr), m_action(nullptr)
		{

		}
		ActionTarget(Entity* target, boost::shared_ptr<Entity> action) : 
			m_originalTarget(target), m_finalTarget(target), m_action(action)
		{
			
		}
		Entity* m_originalTarget;
		Entity* m_finalTarget;
		boost::shared_ptr<Entity> m_action;
	};
	//typedef std::pair<Entity*, boost::shared_ptr<Entity>> ActionTarget;
	class ActionGroup
	{
	public:

		bool addMember(ActionTarget& member);
		bool addMember(Entity& member, boost::shared_ptr<Entity> action);
		bool addMember(const std::string& name, Entity& member, boost::shared_ptr<Entity> action);

		void pushActionToAllMembers(Entity* rootAction);
		void pushActionToAllMembers(boost::shared_ptr<Entity> action);

		boost::unordered_map<std::string, ActionTarget>& getMembers();
	protected:
		boost::unordered_map<std::string, ActionTarget> m_members;
	private:
	};
}

#endif