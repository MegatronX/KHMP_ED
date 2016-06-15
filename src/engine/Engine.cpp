#include "Engine.h"
#include <boost/lexical_cast.hpp>
#include <boost/make_shared.hpp>
#include <events/eventtypes/InputActionEvent.h>
#include <stdio.h>
#include <log/Log.h>
#include <Awesomium/DataPak.h>
#include <utilities/BoostOverrides.h>
const unsigned int defaultWidth = 1000;
const unsigned int defaultHeight = 750;



Engine::Engine(const std::string configFile) 
: m_eventManager(this, "EngineEventManager", true), m_configuration(configFile), m_gameWindow(sf::VideoMode(defaultWidth, defaultHeight), "Kingdom Hearts MP"),
m_audioSystem(this), m_lastUpdate(sf::Time::Zero), m_timedInputController(this), m_awesomiumManager(this), m_screenManager(this)//, m_contentManager()
{
	unsigned int width = 1000;
	unsigned int height = 750;
	unsigned int fps = 60;
	std::string debugLog("Debug.log");
	std::string errorLog("Error.log");
	Logger::setDebugLog(debugLog);
	Logger::setErrorLog(errorLog);
	LOG_DEBUG("Opened debug log file");
	width = m_configuration.getApplicationSetting("width", width);
	height = m_configuration.getApplicationSetting("height", height);
	fps = m_configuration.getApplicationSetting("FPS", fps);
	if (width != defaultWidth || height != defaultHeight)
	{
		sf::Vector2u res(width, height);
		m_gameWindow.setSize(res);
	}

	sf::String title("Kingdom Hearts MP");
	
	m_gameWindow.setTitle(title);
	m_gameWindow.setFramerateLimit(fps);
	m_inputModule.load(configFile, this);
	//Audio engine setup
	unsigned int channels = m_configuration.getApplicationSetting<unsigned int>("SoundChannels", 0);
	std::string musicRoot = m_configuration.getApplicationSetting("ResourcesBaseDirectory") + m_configuration.getApplicationSetting("MusicSubDir");
	std::string seRoot = m_configuration.getApplicationSetting("ResourcesBaseDirectory") + m_configuration.getApplicationSetting("SoundEffectsDir");
	m_audioSystem.initSystem(channels, musicRoot, seRoot);

	std::string htmlRoot = /*m_configuration.getApplicationSetting("ResourcesBaseDirectory") + */m_configuration.getApplicationSetting("HTMLSubDir");
	std::string htmltest = htmlRoot + m_configuration.getApplicationSetting("HTMLTestPak");
	std::string htmlPrefix = m_configuration.getApplicationSetting("HTMLFilePrefix");
	m_awesomiumManager.setHTMLRoot(htmlPrefix);
	m_awesomiumManager.setHTMLFilePrefix(htmlPrefix);
	bool makePak = m_configuration.getApplicationSetting<bool>("MakePak", false);
	if (makePak)
	{
		remove(htmltest.c_str());
		Awesomium::WebString outFile(Awesomium::ToWebString(htmltest));
		Awesomium::WebString inDir(Awesomium::ToWebString(htmlRoot));
		unsigned short pakedFiles = 0;
		Awesomium::WriteDataPak(outFile, inDir, Awesomium::WebString(), pakedFiles);
	}
	m_awesomiumManager.addPakFile("KHMP", htmltest);
	//m_eventManager.setManager(&m_eventManager);
	LOG_DEBUG("Engine initialized. Game Resolution set to " << width << "x" << height);
}

Engine::~Engine()
{
	Logger::getDebugLogStream().close();
	Logger::getErrorLogStream().close();
}

sf::RenderWindow& Engine::getGameWindow()
{
	return m_gameWindow;
}

bool Engine::update()
{
	sf::Time time = getRealTime();
	sf::Time deltaTime = time - m_lastUpdate;
	m_eventManager.tick(sf::milliseconds(10));
	m_timedInputController.update(time);
	m_awesomiumManager.update(time);
	m_screenManager.update(time);
	m_lastUpdate = time;
	return true;
}

void Engine::draw()
{
	m_gameWindow.clear();
	m_screenManager.draw(m_gameWindow);
	m_gameWindow.display();
}

void Engine::pollWindowEvents()
{
	pollWindowEvents(m_gameWindow);
}
void Engine::pollWindowEvents(sf::RenderWindow& window)
{
	using namespace Input;
	sf::Event event;
	while (window.pollEvent(event))
	{
		/* Possible Window Events
		Closed,                 ///< The window requested to be closed (no data)
		Resized,                ///< The window was resized (data in event.size)
		LostFocus,              ///< The window lost the focus (no data)
		GainedFocus,            ///< The window gained the focus (no data)
		TextEntered,            ///< A character was entered (data in event.text)
		KeyPressed,             ///< A key was pressed (data in event.key)
		KeyReleased,            ///< A key was released (data in event.key)
		MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel)
		MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
		MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
		MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
		MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
		MouseLeft,              ///< The mouse cursor left the area of the window (no data)
		JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
		JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
		JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
		JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
		JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)

		Count
		*/
		switch (event.type)
		{
		case sf::Event::Closed:
		case sf::Event::Resized:
		case sf::Event::LostFocus:
		case sf::Event::GainedFocus:
		case sf::Event::JoystickConnected:
		case sf::Event::JoystickDisconnected:
			{
				//auto ev = boost::make_shared<GameWindowEvent>(event, this->getRealTime());
				//m_eventManager.triggerEvent(ev);
			}
			break;
		case sf::Event::JoystickButtonPressed:
		case sf::Event::JoystickButtonReleased:
			{
				bool pushed = event.type == sf::Event::JoystickButtonPressed;
				for (unsigned int i = 0; i < MaxPlayerCount; ++i)
				{
					PlayerInput pIn = static_cast<PlayerInput>(i);
					auto& pset = m_inputModule.getPlayerInput(pIn);
					auto it = pset.getJoypadInputMap().find(event.joystickButton.button);
					if (it != pset.getJoypadInputMap().end())
					{
						auto ev = boost::make_shared<InputActionEvent>(it->second, pushed, pIn, &m_inputModule, this->getRealTime());
						m_eventManager.triggerEvent(ev);
					}

				}
				//auto ev = std::make_shared<InputActionEvent>()
			}
			break;
		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
			{
				bool pushed = event.type == sf::Event::KeyPressed;
				for (unsigned int i = 0; i < MaxPlayerCount; ++i)
				{
					PlayerInput pIn = static_cast<PlayerInput>(i);
					auto& pset = m_inputModule.getPlayerInput(pIn);
					auto it = pset.getKeyboardInputMap().find(event.key.code);
					if (it != pset.getKeyboardInputMap().end())
					{
						auto ev = boost::make_shared<InputActionEvent>(it->second, pushed, pIn, &m_inputModule, this->getRealTime());
						m_eventManager.triggerEvent(ev);
					}
				}
			}
			break;
		default:
			break;
		}
	}
}
IEventManager& Engine::getEventManager()
{
	return m_eventManager;
}
TimeModule& Engine::getTimeModule()
{
	return m_timeModule;
}
TimedInputController& Engine::getTimedInputController()
{
	return m_timedInputController;
}
const ApplicationConfiguration& Engine::getConfiguration()
{
	return m_configuration;
}
AwesomiumManager& Engine::getAwesomiumManager()
{
	return m_awesomiumManager;
}
ScreenManager& Engine::getScreenManager()
{
	return m_screenManager;
}
AudioSystem& Engine::getAudioSystem()
{
	return m_audioSystem;
}
EntityFactory& Engine::getEntityFactory()
{
	return m_entityFactory;
}

ContentManager& Engine::getContentManager()
{
	return m_contentManager;
}

sf::Time Engine::getGameTime() const
{
	return m_timeModule.getGameTime();
}

sf::Time Engine::getRealTime() const
{
	return m_timeModule.getRealTime();
}

int Engine::getUID()
{
	return ++m_idIncrementer;
}