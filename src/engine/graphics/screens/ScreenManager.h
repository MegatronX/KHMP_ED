#pragma once

#ifndef _SCREENMANAGER_H_
#define _SCREENMANAGER_H_

#include <input/controls/InputReceiver.h>
#include <graphics/screens/Screen.h>
#include <deque>
#include <events/IEvent.h>
class Engine;
class ScreenManager;
class ScreenManagerEntry : public IAnimatedDraw, public Input::InputReceiver
{
public:
	ScreenManagerEntry(screen_ptr screen, const bool takeInputWhenInactive = false, const bool drawWhenInactive = true, const bool updateWhenInActive = true, const bool expires = false, const sf::Time expTime = sf::Time::Zero);
	screen_ptr getScreen() const;

	virtual bool handleInput(ev_ptr inputEvent) override;

	void update(const sf::Time& time) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const override;

	bool getExpires() const;
	sf::Time getExpiryTime() const;
	bool getUpdatesWhenNotActive() const;
	bool getTakeInputWhenNotActive() const;
	bool isActive() const;
	void setActive(const bool active);
	bool getDrawWhenNotActive() const;

	bool getMarkedForRemoval() const;
	void setRemove(const bool remove = true);
	unsigned int getID() const;
protected:
	screen_ptr m_screen;
	//Draw priority for screen. Used to force certain screens to front
	unsigned int m_priority;
	//whether draw priority actually does anything
	bool m_usepriority;
	//If entry has an expiry time, this is the time the screen expires
	sf::Time m_popTime;
	//says whether the screen expires from the stack. When the screen expires, pop it from the stack
	bool m_expires;

	bool m_takeInputWhenNotActive;
	bool m_drawWhenNotActive;
	bool m_updateWhenNotActive;
	bool m_active;
	bool m_remove;
	unsigned int m_id;

	friend class ScreenManager;
};
class ScreenManager : public IAnimatedDraw, public Input::InputReceiver
{
public:
	ScreenManager(Engine* engine);
	virtual ~ScreenManager();
	void pushEntry(screen_ptr screen, const bool takeInputWhenInactive = false, const bool drawWhenInactive = true, const bool updateWhenInActive = true, const bool expires = false, const sf::Time expTime = sf::Time::Zero);
	void pushEntry(ScreenManagerEntry& entry);
	void popEntry();
	bool removeEntry(const unsigned int id);
	ScreenManagerEntry& getTopEntry();
	ScreenManagerEntry& getBottomEntry();

	unsigned int getEntryCount();

	ScreenManagerEntry createEntry();

	virtual bool handleInput(ev_ptr inputEvent) override;

	void update(const sf::Time& time) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const override;
protected:
	bool handleNewWindowEvent(ev_ptr event);
	void switchActiveScreen();
	void pushQueuedAdds();
	ScreenManagerEntry* m_activeEntry;
	unsigned int m_entryIDCounter;
private:
	std::deque<ScreenManagerEntry> m_screenStack;
	std::vector<ScreenManagerEntry> m_overlays;
	std::vector<ScreenManagerEntry> m_queuedAdds;
	Engine* m_engine;
	bool m_inputHandlerConnected;
};

#endif