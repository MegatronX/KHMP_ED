#include <boost/make_shared.hpp>

#include "ComponentCreators.h"
#include <entity/EntityFactory.h>
#include <character/BaseCharacterComponent.h>
#include <components/StatManagerComponent.h>

#include <components/ElementalComponent.h>
#include <components/BattleCharacterComponent.h>
#include <actions/Attack.h>

namespace KHMP
{
	void registerComponentCreators(EntityFactory& registerTo)
	{
		registerTo.registerComponentCreator("StatManagerComponent", StatManagerComponent::m_componentType, ComponentCreator(createStatManagerComponent));
		registerTo.registerComponentCreator("StatComponent", StatComponent::m_componentType, ComponentCreator(createStatComponent));
		registerTo.registerComponentCreator("ElementalComponent", ElementalComponent::m_componentType, ComponentCreator(createElementalComponent));
		registerTo.registerComponentCreator("CharacterComponent", BaseCharacterComponent::m_componentType, ComponentCreator(createCharacterComponent));
		registerTo.registerComponentCreator("BattleCharacterComponent", BattleCharacterComponent::m_componentType, ComponentCreator(createBattleCharacterComponent));
	}

	boost::shared_ptr<Component> createStatComponent(pugi::xml_node&, Entity* owner, EntityFactory& factory)
	{
		boost::shared_ptr<StatComponent> sc = boost::make_shared<StatComponent>(owner, factory.getNextComponentID());

		return sc;
	}

	boost::shared_ptr<Component> createStatManagerComponent(pugi::xml_node& node, Entity* owner, EntityFactory& factory)
	{
		boost::shared_ptr<StatManagerComponent> sm = boost::make_shared<StatManagerComponent>(owner, factory.getNextComponentID());

		for (auto childNode = node.children().begin(); childNode != node.children().end(); ++childNode)
		{
			std::string nodeName = std::string(childNode->name());
			if (nodeName == std::string("RawStats"))
			{
				bool valid = true;
				auto& rawStats = sm->getStatComponent(valid, "raw");
				for (auto statProp = childNode->attributes_begin(); statProp != childNode->attributes_end(); ++statProp)
				{
					auto statMatch = NameStatLookup.find(statProp->name());
					if (statMatch != NameStatLookup.end())
					{
						rawStats.setStatValue(statMatch->second, statProp->as_int());
					}
				}
			}
			else if (nodeName == std::string("RawStatMultipliers"))
			{
				bool valid = true;
				auto& rawStats = sm->getStatComponent(valid, "raw");
				for (auto statProp = childNode->attributes_begin(); statProp != childNode->attributes_end(); ++statProp)
				{
					auto statMatch = NameStatLookup.find(statProp->name());
					if (statMatch != NameStatLookup.end())
					{
						rawStats.setStatMultiplier(statMatch->second, statProp->as_float());
					}
				}
			}
		}

		return sm;
	}

	boost::shared_ptr<Component> createElementalComponent(pugi::xml_node& node, Entity* owner, EntityFactory& factory)
	{
		auto ec = boost::make_shared<ElementalComponent>(owner, factory.getNextComponentID());
		for (auto childNode = node.children().begin(); childNode != node.children().end(); ++childNode)
		{
			std::string nodeName = std::string(childNode->name());
			if (nodeName == std::string("Moderator"))
			{
				auto modValString = childNode->value();
				float modVal = boost::lexical_cast<float>(modValString);
				ec->setModerator(modVal);
				//ec->setModerator
			}
			else if (nodeName == std::string("Ceiling"))
			{
				auto ceilValString = childNode->value();
				float ceilVal = boost::lexical_cast<float>(ceilValString);
				ec->setCeiling(ceilVal);
				//ec->setModerator
			}
			else if (nodeName == std::string("Floor"))
			{
				auto flValString = childNode->value();
				float flVal = boost::lexical_cast<float>(flValString);
				ec->setFloor(flVal);
				//ec->setModerator
			}
			else if (nodeName == std::string("ElementWeight"))
			{
				auto weightStr = childNode->value();
				bool abs = false;
				auto eleAttr = childNode->attribute("element");
				if (!eleAttr.empty())
				{
					auto it = Elements::NameElementMap.find(eleAttr.as_string());
					if (it != Elements::NameElementMap.end())
					{
						Elements::Element element = it->second;
						auto absAttr = childNode->attribute("absolute");
						if (absAttr.empty())
							absAttr = childNode->attribute("abs");
						if (!absAttr.empty())
						{
							abs = absAttr.as_bool();
						}
						float weight = boost::lexical_cast<float>(weightStr);
						ec->addElement(element, weight, abs);
					}
				}
			}
		}
		return ec;
	}
	boost::shared_ptr<Component> createCharacterComponent(pugi::xml_node&, Entity* owner, EntityFactory& factory)
	{
		auto ch = boost::make_shared<BaseCharacterComponent>(owner, factory.getNextComponentID());

		return ch;
	}
	boost::shared_ptr<Component> createBattleCharacterComponent(pugi::xml_node&, Entity* owner, EntityFactory& factory)
	{
		///auto ch = boost::make_shared<BattleCharacterComponent>(owner, factory.getNextComponentID());

		return boost::shared_ptr<Component>();// ch;
	}

	boost::shared_ptr<Component> createActionComponent(pugi::xml_node& node, Entity* owner, EntityFactory& factory)
	{
		auto act = boost::make_shared<Action>(owner, factory.getNextComponentID());
		for (auto childNode = node.children().begin(); childNode != node.children().end(); ++childNode)
		{
			std::string nodeName = std::string(childNode->name());
		}
		return act;
	}

	boost::shared_ptr<Component> createAttackComponent(pugi::xml_node& node, Entity* owner, EntityFactory& factory)
	{
		auto atk = boost::make_shared<Attack>(owner, factory.getNextComponentID());
		for (auto childNode = node.children().begin(); childNode != node.children().end(); ++childNode)
		{
			std::string nodeName = std::string(childNode->name());
		}
		return atk;
	}
}