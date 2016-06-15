/****

Used to implement custom action use behaviour. Battle Mechanics will
check for this component, and if it exists, defer management of the 
effects of this action to this component

***/
#pragma once
#ifndef _ACTIONUSECOMPONENT_H_
#define _ACTIONUSECOMPONENT_H_

#include <actions/Action.h>

namespace KHMP
{
	class Mechanics;
	class Battlefield;
	class ActionUseComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0x31f92fa4;
		ActionUseComponent(Entity* owner, Action& actiontarget, ComponentID id) : Component(owner, m_componentType, id), m_action(&actiontarget)
		{

		}

		Action* getAttachedAction() const
		{
			return m_action;
		}

		virtual void setAction(Action& action)
		{
			m_action = &action;
		}



		virtual void use(Mechanics& mechanics, Battlefield& field) = 0;
	protected:
		Action* m_action;
	};
}

#endif