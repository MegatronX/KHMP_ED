#pragma once
#ifndef _ACTIONPROPROCESSCOMPONENT_H_
#define _ACTIONPREPROCESSCOMPONENT_H_

#include <component/Component.h>
#include <actions/Action.h>
#include <utility/Priority.h>
namespace KHMP
{
	class BattleField;
	class Mechanics;

	class ActionPreprocessComponent : public Component, public Priority
	{
	public:
		static const ComponentType m_componentType = 0x343440d4;
		ActionPreprocessComponent(Entity* owner, ComponentID id, const int priority) : Component(owner, m_componentType, id), Priority(priority)
		{

		}

		virtual bool preProcessAction(Action& action, BattleField& field, Mechanics& mechanics) = 0;

	protected:
	};
}

#endif