#include <graphics/screens/ScreenManager.h>
#include <log/Log.h>
#include <Engine.h>
#include <boost/make_shared.hpp>
#include <events/IEventManager.h>
#include <events/eventtypes/InputActionEvent.h>
#include <events/eventtypes/NewAwesomiumScreenEvent.h>
#include <events/eventtypes/PopWindowEvent.h>
#include <graphics/screens/AwesomiumScreen.h>

ScreenManagerEntry::ScreenManagerEntry(screen_ptr screen, const bool takeInputWhenInactive, const bool drawWhenInactive, const bool updateWhenInActive, const bool expires, const sf::Time expTime) :
m_screen(screen), m_takeInputWhenNotActive(takeInputWhenInactive), m_drawWhenNotActive(drawWhenInactive), m_updateWhenNotActive(updateWhenInActive), m_expires(expires), m_popTime(expTime), m_remove(false), m_active(false)
{
	this->m_draw = true;
	screen->setIsDrawing(m_draw);
}

screen_ptr ScreenManagerEntry::getScreen() const
{
	return m_screen;
}

bool ScreenManagerEntry::handleInput(ev_ptr inputEvent)
{
	if (inputEvent && m_screen)
	{
		return m_screen->handleInput(inputEvent);
	}
	return false;
}

void ScreenManagerEntry::update(const sf::Time& time)
{
	if (m_screen)
	{
		m_screen->update(time);
	}
}
void ScreenManagerEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_draw && m_screen)
	{
		target.draw((*m_screen), states);
	}
}

bool ScreenManagerEntry::getExpires() const
{
	return m_expires;
}
sf::Time ScreenManagerEntry::getExpiryTime() const
{
	return m_popTime;
}
bool ScreenManagerEntry::getUpdatesWhenNotActive() const
{
	return m_updateWhenNotActive;
}

bool ScreenManagerEntry::getTakeInputWhenNotActive() const
{
	return m_takeInputWhenNotActive;
}

bool ScreenManagerEntry::isActive() const
{
	return m_active;
}
void ScreenManagerEntry::setActive(const bool active)
{
	m_active = active;
}
bool ScreenManagerEntry::getDrawWhenNotActive() const
{
	return m_drawWhenNotActive;
}

bool ScreenManagerEntry::getMarkedForRemoval() const
{
	return m_remove;
}
void ScreenManagerEntry::setRemove(const bool remove)
{
	m_remove = remove;
}
unsigned int ScreenManagerEntry::getID() const
{
	return m_id;
}
ScreenManager::ScreenManager(Engine* engine) : m_entryIDCounter(0), m_engine(engine), m_inputHandlerConnected(false), m_activeEntry(nullptr)
{
	if (engine)
	{
		engine->getEventManager().addListener(fastdelegate::MakeDelegate(this, &ScreenManager::handleInput), InputActionEvent::m_eventSignature);
		engine->getEventManager().addListener(fastdelegate::MakeDelegate(this, &ScreenManager::handleNewWindowEvent), NewAwesomiumScreenEvent::m_eventSignature);
		engine->getEventManager().addListener(fastdelegate::MakeDelegate(this, &ScreenManager::handleNewWindowEvent), PopWindowEvent::m_eventSignature);
		m_inputHandlerConnected = true;

	}
}

ScreenManager::~ScreenManager()
{
	if (m_inputHandlerConnected)
	{
		m_engine->getEventManager().removeListener(fastdelegate::MakeDelegate(this, &ScreenManager::handleInput), InputActionEvent::m_eventSignature);
		m_engine->getEventManager().removeListener(fastdelegate::MakeDelegate(this, &ScreenManager::handleNewWindowEvent), NewAwesomiumScreenEvent::m_eventSignature);
		m_engine->getEventManager().removeListener(fastdelegate::MakeDelegate(this, &ScreenManager::handleNewWindowEvent), PopWindowEvent::m_eventSignature);
		m_inputHandlerConnected = false;
	}
}

void ScreenManager::pushEntry(screen_ptr screen, const bool takeInputWhenInactive, const bool drawWhenInactive, const bool updateWhenInActive, const bool expires, const sf::Time expTime)
{
	ScreenManagerEntry entry(screen, takeInputWhenInactive, drawWhenInactive, updateWhenInActive, expires, expTime);
	entry.m_id = m_entryIDCounter++;
	if (entry.m_screen)
		entry.m_screen->setStackID(entry.m_id);
	pushEntry(entry);
}
void ScreenManager::pushEntry(ScreenManagerEntry& entry)
{
	m_queuedAdds.push_back(entry);
}
void ScreenManager::popEntry()
{
	if (!m_screenStack.empty())
	{
		m_screenStack.front().setRemove(true);
		if (m_screenStack.size() > 1)
		{
			m_activeEntry->setActive(false);
			m_activeEntry = &m_screenStack[1];
			m_activeEntry->setActive(true);
		}
	}
	else
	{
		LOG_DEBUG("Attempted to pop empty screen stack");
	}
}
bool ScreenManager::removeEntry(const unsigned int id)
{
	bool found = false;
	for (auto stack = m_screenStack.begin(); stack != m_screenStack.end(); ++stack)
	{
		if (stack->getID() == id)
		{
			stack->setRemove(true);
			found = true;
			if (stack->getID() == m_activeEntry->getID())
			{
				m_activeEntry->setActive(false);
				for (auto newActiveStack = m_screenStack.begin(); newActiveStack != m_screenStack.end(); ++newActiveStack)
				{
					if (!newActiveStack->getMarkedForRemoval())
					{
						m_activeEntry = &(*newActiveStack);
						m_activeEntry->setActive(true);
						break;
					}
				}
			}
		}
	}
	return found;
}
bool ScreenManager::handleInput(ev_ptr inputEvent)
{
	bool inputProcessed = false;
	for (auto it = m_overlays.begin(); it != m_overlays.end(); ++it)
	{
		if (it->isActive() || it->getTakeInputWhenNotActive())
		{
			inputProcessed |= it->handleInput(inputEvent);
		}
		/*if (!(it->getExpires()) || !(it->getExpires() && it->getExpiryTime() < time))
		{
		}*/
	}
	for (auto it = m_screenStack.begin(); it != m_screenStack.end() && !inputProcessed; ++it)
	{
		if (it->isActive() || it->getTakeInputWhenNotActive())
		{
			inputProcessed |= it->handleInput(inputEvent);
			//it->draw(target, states);
		}
	}
	pushQueuedAdds();
	return inputProcessed;
}

void ScreenManager::update(const sf::Time& time)
{
	std::vector<std::vector<ScreenManagerEntry>::iterator> m_removals;
	for (auto it = m_overlays.begin(); it != m_overlays.end(); ++it)
	{
		if ((it->getExpires() && it->getExpiryTime() < time) || it->getMarkedForRemoval())
		{
			m_removals.push_back(it);
		}
		else if (it->getUpdatesWhenNotActive() || (it->isActive()))
		{
			it->update(time);
		}
	}
	for (auto rm = m_removals.begin(); rm != m_removals.end(); ++rm)
	{
		m_overlays.erase(*rm);
	}
	std::vector<std::deque<ScreenManagerEntry>::iterator> m_stackRemovals;
	for (auto it = m_screenStack.begin(); it != m_screenStack.end(); ++it)
	{
		if ((it->getExpires() && it->getExpiryTime() < time) || it->getMarkedForRemoval())
		{
			m_stackRemovals.push_back(it);
		}
		else if (it->getUpdatesWhenNotActive() || (it->isActive()))
		{
			it->update(time);
		}
	}
	for (auto rm = m_stackRemovals.begin(); rm != m_stackRemovals.end(); ++rm)
	{
		m_screenStack.erase(*rm);
	}
	if (m_stackRemovals.size() > 0)
	{
		m_activeEntry = m_screenStack.size() > 0 ? &(m_screenStack.front()) : nullptr;
	}
	pushQueuedAdds();
}
void ScreenManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto it = m_screenStack.rbegin(); it != m_screenStack.rend(); ++it)
	{
		if (it->isActive() || it->getDrawWhenNotActive())
		{
			it->draw(target, states);
		}
	}
}

bool ScreenManager::handleNewWindowEvent(ev_ptr event)
{
	bool handled = false;
	if (event->getEventType() == NewAwesomiumScreenEvent::m_eventSignature)
	{
		auto awWinEvent = boost::dynamic_pointer_cast<NewAwesomiumScreenEvent>(event);
		if (awWinEvent)
		{
			auto awscreenptr = boost::make_shared<AwesomiumScreen>(m_engine, awWinEvent->getWidth(), awWinEvent->getHeight());
			awscreenptr->setURL(awWinEvent->getURL());// ("http://www.google.com");
			pushEntry(awscreenptr, false);
			handled = true;
		}
	}
	else if (event->getEventType() == PopWindowEvent::m_eventSignature)
	{
		auto rmScreen = boost::dynamic_pointer_cast<PopWindowEvent>(event);
		if (rmScreen)
		{
			if (rmScreen->popTopWindow())
			{
				popEntry();
			}
			else if (rmScreen->useAwesomiumWindowPtr())
			{
				auto wv = rmScreen->getWebView();
				for (auto stack = m_screenStack.begin(); stack != m_screenStack.end(); ++stack)
				{
					auto screenPtr = stack->getScreen();
					auto awScreen = boost::dynamic_pointer_cast<AwesomiumScreen>(screenPtr);
					if (awScreen)
					{
						if (awScreen->getWebView()->process_id() == wv->process_id())
						{
							removeEntry(stack->getID());
							handled = true;
							break;
						}
					}
				}
			}
			else
			{
				removeEntry(rmScreen->popWindowID());
				handled = true;
			}
		}
	}
	return handled;
}

void ScreenManager::pushQueuedAdds()
{
	for (auto entry = m_queuedAdds.rbegin(); entry != m_queuedAdds.rend(); ++entry)
	{
		m_screenStack.push_front(*entry);
		if (m_activeEntry)
		{
			m_activeEntry->setActive(false);
			
		}
		m_activeEntry = &(m_screenStack.front());
		m_activeEntry->setActive(true);
	}
	m_queuedAdds.clear();
}