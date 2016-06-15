#pragma once
#ifndef _MULTIACTIONCOMPONENT_H_
#define _MULTIACTIONCOMPONENT_H_

#include <vector>
#include <boost/unordered_map.hpp>

#include <component/Component.h>

namespace KHMP
{
	class MultiActionComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0x4fbf5dfb;
		MultiActionComponent(Entity* owner, ComponentID id);

		void addSubAction(boost::shared_ptr<Entity> action);
		void addSubAction(const std::string& index, boost::shared_ptr<Entity> action);
		bool removeSubAction(boost::shared_ptr<Entity> action);
		bool removeSubAction(const std::string& actionName);
		bool removeSubAction(const std::string& index, boost::shared_ptr<Entity> action);
		void clearSubActions();
		boost::unordered_map<std::string, std::vector<boost::shared_ptr<Entity> > >& getSubActions()
		{
			return m_subActions;
		}
		bool hasSubActions() const;
	protected:
		boost::unordered_map<std::string, std::vector<boost::shared_ptr<Entity> > > m_subActions;
		
	private:
	};

}

#endif