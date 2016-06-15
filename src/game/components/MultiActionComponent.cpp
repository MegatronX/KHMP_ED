#include <components/MultiActionComponent.h>
#include <entity/Entity.h>

namespace KHMP
{
	MultiActionComponent::MultiActionComponent(Entity* owner, ComponentID id) : Component(owner, m_componentType, id)
	{

	}

	void MultiActionComponent::addSubAction(boost::shared_ptr<Entity> action)
	{
		//m_subAction
		m_subActions[action->getEntityName()].push_back(action);
	}
	void MultiActionComponent::addSubAction(const std::string& index, boost::shared_ptr<Entity> action)
	{
		m_subActions[index].push_back(action);
	}
	bool MultiActionComponent::removeSubAction(boost::shared_ptr<Entity> action)
	{
		bool removed = false;
		for (auto it = m_subActions.begin(); it != m_subActions.end(); ++it)
		{
			for (auto act = it->second.begin(); act != it->second.end();)
			{
				if ((*act)->getEntityName() == action->getEntityName())
				{
					act = it->second.erase(act);
					removed = true;
				}
				else
				{
					++act;
				}
			}
		}
		return removed;
	}
	bool MultiActionComponent::removeSubAction(const std::string& actionName)
	{
		bool removed = false;
		for (auto it = m_subActions.begin(); it != m_subActions.end(); ++it)
		{
			for (auto act = it->second.begin(); act != it->second.end();)
			{
				if ((*act)->getEntityName() == actionName)
				{
					act = it->second.erase(act);
					removed = true;
				}
				else
				{
					++act;
				}
			}
		}
		return removed;
	}

	bool MultiActionComponent::removeSubAction(const std::string& index, boost::shared_ptr<Entity> action)
	{
		bool removed = false;

		auto it = m_subActions.find(index);
		if (it != m_subActions.end())
		{
			for (auto act = it->second.begin(); act != it->second.end();)
			{
				if ((*act)->getEntityName() == action->getEntityName())
				{
					act = it->second.erase(act);
					removed = true;
				}
				else
				{
					++act;
				}
			}
		}

		return removed;
	}
	void MultiActionComponent::clearSubActions()
	{
		m_subActions.clear();
	}
	bool MultiActionComponent::hasSubActions() const
	{
		bool hasSubActions = false;
		for (auto it = m_subActions.begin(); it != m_subActions.end(); ++it)
		{
			if (it->second.size() > 0)
			{
				hasSubActions = true;
				break;
			}
		}
		return hasSubActions;
	}
}