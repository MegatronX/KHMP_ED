#include <boost/make_shared.hpp>

#include "EngineTests.h"
#include <events/eventtypes/InputActionEvent.h>
#include <events/eventtypes/AudioEvents.h>
#include <components/StatManagerComponent.h>
#include <entity/Entity.h>
#include <entity/EntityFactory.h>
#include <events/StatChangeEvent.h>
#include <events/ActionProcessedEvent.h>
#include <components/ComponentCreators.h>
#include <components/MultiActionComponent.h>
#include <input/controls/TimedInputController.h>
#include <events/eventtypes/TimingWindowEvents.h>
#include <graphics/screens/AwesomiumScreen.h>
#include <graphics/screens/ScreenManager.h>
#include <log/Log.h>

#include <battle/Mechanics.h>
#include <battle/BattleField.h>
#include <actions/Attack.h>

#include <graphics/BigTexture.h>
#include <graphics/BigSprite.h>

//#include 
using namespace KHMP;
using namespace pugi;

void writePakFile(std::string inputDir, std::string outputName)
{
	Awesomium::WebString outFile(Awesomium::ToWebString(outputName));
}
bool inputEventTest(ev_ptr data)
{
	auto inputActionData = boost::static_pointer_cast<InputActionEvent>(data);
	std::cout << (inputActionData->isActionPushed() ? "Pushed " : "Released ") << Input::ActionNameLookup.find(inputActionData->getAction())->second << "\n";
	return false;
}

bool testEngine(Engine* engine)
{
	engine->getEventManager().addListener(EventListener(inputEventTest), InputActionEvent::m_eventSignature);
	return true;
}

bool freeEngine(Engine* engine)
{
	engine->getEventManager().removeListener(EventListener(inputEventTest), InputActionEvent::m_eventSignature);
	return true;
}

void subManagerTest(Engine* engine)
{
	auto& evMng = engine->getEventManager();
	boost::shared_ptr<Entity> ent = boost::make_shared<Entity>(10101021, "Arian2");
	auto stMng = boost::make_shared<StatManagerComponent>(ent.get(), 192331);
	ent->addComponent(stMng);
	stMng->registerEventHandlers(&evMng);
}

void bigTextureTest()
{
	sf::Image img;
	img.loadFromFile("D:\\KHMP_ED\\KHMillenniumPast-master\\KHMillenniumPast-master\\resources\\TileMaps\\trees_zorksox.png");

	BigTexture testTexture;
	testTexture.loadFromFile("D:\\KHMP_ED\\KHMillenniumPast-master\\KHMillenniumPast-master\\resources\\TileMaps\\trees_zorksox.png");

	BigSprite testSprite;
	testSprite.setTexture(testTexture);
	testSprite.setTextureRect(sf::IntRect(50, 5000, 40, 40));
	int tempStop = 1;
}

bool statManagerTest(Engine* engine)
{
	auto& evMng = engine->getEventManager();
	boost::shared_ptr<Entity> ent = boost::make_shared<Entity>(1010101, "Arian");
	pugi::xml_document doc;
	boost::shared_ptr<Component> cmp;

	xml_parse_result result = doc.load_file("..\\..\\resources\\databases\\Characters.xml");
	if (!result)
	{
		std::cerr << "Failed to load characters test. Error: " << result.description() << "\n";
	}
	else
	{
		auto charRoot = doc.child("Characters");
		if (charRoot)
		{
			for (xml_node character = charRoot.child("Character"); character; character = character.next_sibling("Character"))
			{
				xml_node componentRoot = character.child("Components");
				for (auto component = componentRoot.children().begin(); component != componentRoot.children().end(); ++component)
				{
					cmp = createStatManagerComponent(*component, ent.get(), engine->getEntityFactory());
				}
			}
			/*for (auto character = charRoot.children.begin(); character != charRoot.children.end(); character->)
			{
				auto components = character->find_child("Components");
				for (auto component = components.children.begin(); component != components.children.end(); ++component)
				{
					if (std::string(component->name) == "StatManagerComponent")
					{
						cmp = createStatManagerComponent(*component, ent.get(), engine->getEntityFactory());
						break;
					}
				}
			}*/
		}
		//auto cmp = createStatManagerComponent(ent.get(), 0);

		auto stMng = boost::make_shared<StatManagerComponent>(ent.get(), 19231);
		ent->addComponent(stMng);
		stMng->registerEventHandlers(&evMng);
		stMng->syncStat(0);
		subManagerTest(engine);
		std::array<int, StatCount> statBoost = { 10, 1, 20, 10, 10, 4, 7, 8, 9, 10, 11, 12, 13, 14 };
		std::array<float, StatCount> statMults = { 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14 };
		boost::shared_ptr<BatchStatChangeRequest> statEvent = boost::make_shared<BatchStatChangeRequest>(engine->getTimeModule().getGameTime(), statBoost, statMults, ent.get());
		statEvent->setStatSet("Equipment");
		evMng.triggerEvent(statEvent);

		//evMng.queueEvent(statEvent);

		return true;
	}
	
	return false;
}

bool musicTest(Engine* engine, std::string musicFile)
{
	auto addAudio = boost::make_shared<AddAudioRequestEvent>(musicFile, musicFile, engine->getTimeModule().getGameTime());
	auto playAudio = boost::make_shared<PlayAudioRequestEvent>(musicFile, 4, true, 1.f, engine->getTimeModule().getGameTime());

	engine->getEventManager().queueEvent(addAudio);
	engine->getEventManager().queueEvent(playAudio);

	return true;
}

bool timingWindowReceiver(ev_ptr timingEvent)
{
	if (timingEvent->getEventType() == TimingWindowEvent::m_eventSignature)
	{
		auto tevent = boost::dynamic_pointer_cast<TimingWindowEvent>(timingEvent);
		if (tevent.get() != nullptr)
		{
			if (tevent->getTimingWindowID() == 0xFF21)
			{
				if (tevent->getWindowHit())
				{
					std::cout << "Hit timing window!\n";
				}
				else if (tevent->getWindowMissed())
				{
					std::cout << "Missed timing window!\n";
				}
				else if (tevent->getWindowExpired())
				{
					std::cout << "Timing Window expired!\n";
				}
			}
			return true;
		}
		else
		{
			LOG_ERROR("Tried to convert non timing window event into a timing window event");
		}
	}
	return false;
}

bool timingWindowTest(Engine* engine)
{
	engine->getEventManager().addListener(EventListener(timingWindowReceiver), TimingWindowEvent::m_eventSignature);
	auto& timedInputController = engine->getTimedInputController();
	TimingWindow window(engine->getGameTime(), engine->getGameTime() + sf::seconds(30.5));
	timedInputController.openTimingWindow(Input::P1Input, Input::InputAction::Down, engine->getGameTime(), engine->getGameTime() + sf::seconds(30.f),
		true, true, false, true, 0xFF21);

	return true;

}

bool htmlWindowTest(Engine* engine)
{
	auto awscreenptr = boost::make_shared<AwesomiumScreen>(engine, engine->getGameWindow().getSize().x, engine->getGameWindow().getSize().y);
	awscreenptr->setURL("KHMP/TitleScreen.html");// ("http://www.google.com");
	engine->getScreenManager().pushEntry(awscreenptr, false);

//	auto awscreenptr2 = boost::make_shared<AwesomiumScreen>(engine, engine->getGameWindow().getSize().x, engine->getGameWindow().getSize().y);
//	awscreenptr2->setURL("KHMP/NewGameOptions.html");// ("http://www.google.com");
//	engine->getScreenManager().pushEntry(awscreenptr2, false);
	return true;
}

bool mechanicsTest(Engine* engine)
{
	Entity battle(2342425789);
	Mechanics mechanics(&battle, 131486850, engine);
	auto ent = boost::make_shared<Entity>(12393545, "Ceira");
	auto trg = boost::make_shared<Entity>(12393, "Fireblast");
	auto atk = boost::make_shared<Attack>(ent.get(), 239243);
	ent->addComponentAsOnlyInstanceOfType(atk);
	atk->setCriticalHitChance(0.4f);
	
	BattleField field;

	bool crits[100];
	unsigned int critCount = 0;
	for (unsigned int i = 0; i < 100; ++i)
	{
		crits[i] = mechanics.isCriticalHit(ent, trg, field);
		if (crits[i])
			++critCount;
	}

	//Mechanics mechanics()
	return true;
}

bool actionProcessorReceiver(ev_ptr actionEvent)
{
	int stop = 1;
	auto actProcessedEvent = boost::dynamic_pointer_cast<ActionProcessedEvent>(actionEvent);
	if (actProcessedEvent)
	{
		auto action = actProcessedEvent->getAction();
		Attack* atk = dynamic_cast<Attack*>(action);
		if (atk)
		{
			//std::cout << atk->getOwner()->getEntityName() << " damage " << atk->getCalculatedDamage() << "\n";
		}
	}
	return true;
}

bool attacksTest(Engine* engine)
{
	BattleField field;
	auto battle = boost::make_shared<Entity>(42529539, "Randombattle");
	auto mechanics = boost::make_shared<Mechanics>(battle.get(), 313499, engine, 10);
	battle->addComponent(mechanics);

	boost::shared_ptr<Entity> arian = boost::make_shared<Entity>(1010101, "Arian");
	auto stMng = boost::make_shared<StatManagerComponent>(arian.get(), 19231);
	arian->addComponent(stMng);

	boost::shared_ptr<Entity> cactuar = boost::make_shared<Entity>(1018101, "Cactuar");
	auto stMng2 = boost::make_shared<StatManagerComponent>(cactuar.get(), 14231);
	cactuar->addComponent(stMng2);


	auto thousandNeedles = boost::make_shared<Entity>(42529509, "1000 Needles");
	auto multiActionCmp = boost::make_shared<MultiActionComponent>(thousandNeedles.get(), 23430005);
	thousandNeedles->addComponent(multiActionCmp);
	std::cout << "Engine time before creation: " << engine->getRealTime().asMilliseconds() << "\n";
	for (unsigned int i = 0; i < 1000; ++i)
	{
		auto needleAtkEntity = boost::make_shared<Entity>(434321 + i, "1 Needle");
		auto needleAtk = boost::make_shared<Attack>(thousandNeedles, 1121398 + i, 1.f, 1.0);
		needleAtk->addProperty("FixedDamage", "true");
		needleAtkEntity->addFlag("FixedDamage");
		needleAtkEntity->addProperty("FixedDamageAmount", "1");
		needleAtk->addProperty("FixedDamageAmount", "1");
		needleAtkEntity->addComponent(needleAtk);
		needleAtk->getUsers().addMember(*cactuar, needleAtkEntity);
		needleAtk->getTargets().addMember(*arian, needleAtkEntity);
		multiActionCmp->addSubAction(needleAtkEntity);
	}
	engine->getEventManager().addListener(actionProcessorReceiver, ActionProcessedEvent::m_eventSignature);
	std::cout << "Engine time after creation: " << engine->getRealTime().asMilliseconds() << "\n";
	mechanics->useAction(*thousandNeedles, field);
	std::cout << "Engine time after use: " << engine->getRealTime().asMilliseconds() << "\n";
	//mechanics->preProcessAction(*thousandNeedles, field);
	//mechanics->processAction(*thousandNeedles, field);
	//mechanics->postProcessAction(*thousandNeedles, field);

	return true;
}