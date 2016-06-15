#include <entity/GameEntityFactory.h>
#include <log/Log.h>
#include <components/StatChangeOnApplyComponent.h>
#include <boost/make_shared.hpp>
#include <character/Stats.h>
#include <components/StatusEffectComponent.h>
using namespace pugi;
namespace KHMP
{
	//creators
	boost::shared_ptr<Entity> StatusEffectCreator(pugi::xml_node& node, EntityFactory& factory)
	{
		std::string name = node.attribute("name").as_string();
		if (!name.empty())
		{
			auto seEnt = boost::make_shared<Entity>(factory.getNextEntityID(), name);
			int defaultTurns = DefaultSETurns;

			auto seCmp = boost::make_shared<StatusEffectComponent>(seEnt.get(), factory.getNextComponentID(), defaultTurns, defaultTurns);

			xml_node propertiesNode = node.child("Properties");
			if (propertiesNode)
			{
				if (propertiesNode.child("Refreshable"))
				{
					//set refreshable
					seCmp->setIsRefreshable(true);
				}
				else
				{
					//set not refreshable
					seCmp->setIsRefreshable(false);
				}
				if (propertiesNode.child("Positive"))
				{
					seCmp->setIsPositive(true);
				}
				if (propertiesNode.child("Negative"))
				{
					seCmp->setIsPositive(false);
				}
				xml_node turnsNode = propertiesNode.child("DefaultTurns");
				if (turnsNode)
				{
					int turns = boost::lexical_cast<int>(turnsNode.value());
				}
			}
			xml_node replacementList = node.child("ReplacementList");
			if (replacementList)
			{
				for (auto replacement = replacementList.child("StatusEffectEntry"); replacement; replacement = replacementList.next_sibling("StatuseffectEntry"))
				{
					auto seName = std::string(replacement.attribute("name").as_string());
					if (!seName.empty())
					{
						seCmp->addReplacement(seName);
					}
				}
			}
			xml_node cancellationList = node.child("Cancellationlist");
			if (cancellationList)
			{
				for (auto cancellation = cancellationList.child("StatusEffectEntry"); cancellation; cancellation = cancellationList.next_sibling("StatuseffectEntry"))
				{
					auto seName = std::string(cancellation.attribute("name").as_string());
					if (!seName.empty())
					{
						seCmp->addCancelation(seName);
					}
				}
			}
			//auto seCmp = boost::make_shared<StatusEffectComponent>()
			return seEnt;
		}
		return boost::make_shared<Entity>(factory.getNextEntityID());
		//auto statusEffect = boost::make_shared<Entity>
	}
	boost::shared_ptr<Component> StatChangeOnApplyComponenetCreator(pugi::xml_node& node, Entity* owner, EntityFactory& factory)
	{
		auto cmp = boost::make_shared<StatChangeOnApplyComponent>(owner, factory.getNextComponentID());
		for (xml_node stChg = node.child("StatChange"); stChg; stChg = stChg.next_sibling("StatChange"))
		{
			std::string stName;
			int stAdd = 0;
			float stMult = 1.f;
			
			xml_attribute attr = stChg.attribute("add");
			if (!attr.empty())
			{
				stAdd = attr.as_int();
			}
			attr = stChg.attribute("mult");
			if (!attr.empty())
			{
				stMult = attr.as_float();
			}
			attr = stChg.attribute("stat");
			if (!attr.empty() && (stAdd != 0 || stMult != 1.f))
			{
				stName = std::string(attr.as_string());
				auto stat = NameStatLookup.find(stName);
				if (stat != NameStatLookup.end())
				{
					//add entry to cmp
					if (stAdd != 0)
					{
						cmp->addStatAdder(stat->second, stAdd);
					}
					if (stMult != 1.f)
					{
						cmp->addStatMultiplier(stat->second, stMult);
					}
				}
			}
		}
		xml_node prior = node.child("Priority");
		if (prior)
		{
			int priority = boost::lexical_cast<int>(prior.value());
			cmp->setPriority(priority);
		}
		return cmp;
	}

	//game factory definitions

	GameEntityFactory::GameEntityFactory()
	{
		//register status effect creators
		registerEntityCreator("StatusEffect", EntityCreator(StatusEffectCreator));
		registerComponentCreator("StatChangeOnApplyComponent", ComponentCreator(StatChangeOnApplyComponenetCreator));
	}
	GameEntityFactory::~GameEntityFactory()
	{

	}

	boost::unordered_map<std::string, boost::shared_ptr<Entity> > GameEntityFactory::parseEquipmentDatabase(const std::string& equipDoc)
	{
		boost::unordered_map<std::string, boost::shared_ptr<Entity> > equipment;
		pugi::xml_document eDoc;
		pugi::xml_parse_result result = eDoc.load_file(equipDoc.c_str());
		if (!result)
		{
			LOG_DEBUG("Failed to open " << eDoc << std::endl);
			LOG_DEBUG("Reason: " << result.description() << std::endl);
			return equipment;
			//return m_mapLoaded = false;
		}

		pugi::xml_node resNode = eDoc.child("GameResources");
		pugi::xml_node itemsNode = resNode.child("Items");
		for (auto item = itemsNode.first_child(); item; item = item.next_sibling())
		{
			std::string entName(item.attribute("name").value());
			//item->
			equipment[entName] = createEntity(item);
		}
		return equipment;
	}
	boost::unordered_map<std::string, boost::shared_ptr<Entity> > GameEntityFactory::parseStatusEffectDatabase(const std::string& seDocName)
	{
		boost::unordered_map<std::string, boost::shared_ptr<Entity> > statusEffects;
		pugi::xml_document seDoc;
		pugi::xml_parse_result result = seDoc.load_file(seDocName.c_str());
		if (!result)
		{
			LOG_DEBUG("Failed to open " << seDocName << std::endl);
			LOG_DEBUG("Reason: " << result.description() << std::endl);
			return statusEffects;
			//return m_mapLoaded = false;
		}

		pugi::xml_node resNode = seDoc.child("GameResources");
		pugi::xml_node statusEffectsNode = resNode.child("StatusEffects");
		for (auto se = statusEffectsNode.child("StatusEffect"); se; se = se.next_sibling("StatusEffect"))
		{
			std::string entName(se.attribute("name").value());
			if (!entName.empty())
				statusEffects[entName] = createEntity(se);
		}
		return statusEffects;
	}
	boost::shared_ptr<Entity> GameEntityFactory::createEntity(const std::string& entityType, const std::string& entityName)
	{
		return EntityFactory::createEntity(entityType, entityName);

	}

	boost::shared_ptr<Entity> GameEntityFactory::createEntity(pugi::xml_node& entity)
	{
		return EntityFactory::createEntity(entity);
	}


}