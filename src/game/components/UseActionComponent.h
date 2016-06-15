#pragma once
#ifndef _USEACTIONCOMPONENT_H_
#define _USEACTIONCOMPONENT_H_

#include <component/Component.h>
#include <utility/Priority.h>
namespace KHMP
{
	class Action;
	class BattleField;
	class Mechanics;
	 //used for overall action override
	class UseActionComponent : public Component, public Priority
	{
	public:
		static const ComponentType m_componentType = 0x97dddd2d;
		UseActionComponent(Entity* owner, ComponentID id);

		virtual void UseAction(Action& act, BattleField& field, Mechanics& mechanics);
	};

	//user for vs single target action use override
	class UseActionAgainstTargetComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0xfad32fe2;
		UseActionAgainstTargetComponent(Entity* owner, ComponentID id);

		virtual void UseActionAgainstTarget(Action& act, Entity& ent, Mechanics& mechanics);

	};
}

#endif