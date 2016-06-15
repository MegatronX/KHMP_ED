#pragma once
#ifndef _ITEMCOMPONENT_H_
#define _ITEMCOMPONENT_H_

#include <component/Component.h>
#include <actions/Action.h>
namespace KHMP
{
	class BattleField;
	class Mechanics;
	class ItemComponent : public Component
	{
	public:
		const static ComponentType m_componentType;
		ItemComponent(Entity* owner, const ComponentID id);
		virtual ~ItemComponent();
	protected:

	private:
		unsigned int m_defaultValue;

	};

	class EquippableComponent : public Component
	{
	public:
		const static ComponentType m_componentType = 0xa0a46011;
		EquippableComponent(Entity* owner, const ComponentID id);
		virtual ~EquippableComponent();

		virtual RawClonePtr rawClone() const override;

		virtual int equip(Entity& target) { return 0;  };

		virtual int unEquip(Entity& target) { return 0; };
 
	};
	/*class MultiEquippableComponent : public EquippableComponent
	{
	public:
		MultiEquippableComponent(Entity* owner, const ComponentID id);
		~MultiEquippableComponent();
		MultiEquippableComponent(const MultiEquippableComponent& ref);

		virtual RawClonePtr rawClone() const override;

		virtual int equip(Entity& target) override;
		virtual int unEquip(Entity& target) override;

		virtual bool addEquippableComponent(boost::shared_ptr<EquippableComponent> eqp, const bool replaceExisting = true);
		virtual bool addEquippableComponent(boost::shared_ptr<EquippableComponent> eqp, const bool initCmp, const bool postInitCmp, const bool replaceExisting = true);
		virtual bool removeEquippableComponent(boost::shared_ptr<EquippableComponent> eqp, const bool destroyIfRemoved);
		virtual bool removeEquippableComponent(ComponentID id, const bool destroyIfRemoved);
		virtual boost::shared_ptr<EquippableComponent> getEquippableComponent(ComponentID id);

		MultiEquippableComponent& operator=(const MultiEquippableComponent& ref);
	protected:
		boost::unordered_map<ComponentID, boost::shared_ptr<EquippableComponent> > m_equippableComponents;

	};*/
	//Used to implement consumable items -> potions, elixirs, stat ups, etc.
	class ConsumableComponent : public Component
	{
	public:
		static ComponentType m_componentType;

		ConsumableComponent(Entity* owner, const ComponentID id);
		virtual ~ConsumableComponent();

		virtual RawClonePtr rawClone() const override;

		virtual int consumeItem(Entity& target, Entity* user);

		virtual int consumeItemInBattle(Entity& target, ActionGroup& users, BattleField& field, Mechanics& mechanics);

	};
}

#endif