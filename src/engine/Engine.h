#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <sfml/Graphics.hpp>
#include <events/EventManager.h>
#include <time/TimeModule.h>
#include <input/controls/InputModule.h>
#include <input/controls/TimedInputController.h>
#include <configuration/ApplicationConfiguration.h>
#include <audio/AudioSystem.h>
#include <entity/EntityFactory.h>
#include <contentmanager\ContentManager.h>
#include <iostream>
#include <graphics/awesomium.h>
#include <graphics/screens/ScreenManager.h>

class Engine
{
public:
	Engine(const std::string configFile);
	~Engine();
	sf::RenderWindow& getGameWindow();

	//returns whether the engine is still running
	virtual bool update();
	virtual void draw();
	void pollWindowEvents();
	void pollWindowEvents(sf::RenderWindow& window);

	IEventManager& getEventManager();
	TimeModule& getTimeModule();
	TimedInputController& getTimedInputController();
	const ApplicationConfiguration& getConfiguration();
	//Graphics systems
	AwesomiumManager& getAwesomiumManager();
	ScreenManager& getScreenManager();
	//Audio Systems
	AudioSystem& getAudioSystem();
	//Entity Systems
	EntityFactory& getEntityFactory();

	ContentManager& getContentManager();

	sf::Time getGameTime() const;
	sf::Time getRealTime() const;

	int getUID();
protected:
private:
	sf::RenderWindow m_gameWindow;
	//Settings
	ApplicationConfiguration m_configuration;
	//Modules/Managers
	Input::InputModule m_inputModule;
	TimedInputController m_timedInputController;
	TimeModule m_timeModule;
	EventManager m_eventManager;
	AudioSystem m_audioSystem;
	EntityFactory m_entityFactory;
	AwesomiumManager m_awesomiumManager;
	ScreenManager m_screenManager;
	ContentManager m_contentManager;
	//ID assignment 
	
	int m_idIncrementer;
	sf::Time m_lastUpdate;
};

#endif