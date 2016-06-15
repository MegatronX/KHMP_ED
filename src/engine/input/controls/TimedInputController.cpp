#include <boost/make_shared.hpp>

#include <events/eventtypes/TimingWindowEvents.h>
#include <input/controls/TimedInputController.h>
#include <events/eventtypes/InputActionEvent.h>
#include <Engine.h>
#include <log/Log.h>

InputTimingWindow::InputTimingWindow() : m_closeOnHitTiming(true), m_closeOnMissedTiming(true), m_closeOnWrongInput(true), m_closeOnWrongPlayerInput(false)
{
	
}

InputTimingWindow::InputTimingWindow(const Input::InputAction& action, const TimingWindow& window, const bool closeOnhittiming, const bool closeOnMissedTiming, const bool closeOnWrongInput, const bool closeOnWrongPlayer) 
	: m_window(window), m_closeOnHitTiming(closeOnhittiming), m_closeOnMissedTiming(closeOnMissedTiming), m_closeOnWrongInput(closeOnWrongInput), m_closeOnWrongPlayerInput(closeOnWrongPlayer)
{
	m_onActions.insert(action);
}

TimedInputController::TimedInputController(Engine* engine) : m_engine(engine), m_inputEventHookedUp(false)
{

}
TimedInputController::~TimedInputController()
{

}

void TimedInputController::update(const sf::Time time)
{
	for (auto window = m_openWindows.begin(); window != m_openWindows.end();)
	{
		if (window->second.m_window.getWindowEndTime() < time)
		{
			//dispatch expired event
			dispatchTimingWindowResult(false, false, true, window->second);
			window = m_openWindows.erase(window);
		}
		else
		{
			++window;
		}
	}
	if (m_openWindows.size() == 0 && m_inputEventHookedUp)
	{
		unregisterInputHandler();
	}
}

bool TimedInputController::handleInput(ev_ptr inputEvent)
{
	if (inputEvent->getEventType() == InputActionEvent::m_eventSignature && m_openWindows.size() > 0)
	{
		auto inputEv = boost::dynamic_pointer_cast<InputActionEvent>(inputEvent);
		if (inputEv.get() != nullptr)
		{
			auto window = m_openWindows.find(inputEv->getPlayer());
			if (window != m_openWindows.end())
			{
				if (window->second.m_onActions.find(inputEv->getAction()) != window->second.m_onActions.end())
				{
					if (window->second.m_window.isInWindow(inputEv->getTimeStamp()))
					{
						//dispatch timed event hit
						dispatchTimingWindowResult(true, false, false, window->second);
						//remove event
						if (window->second.m_closeOnHitTiming)
						{
							m_openWindows.erase(window);
						}
					}
					else if (window->second.m_closeOnMissedTiming)
					{
						//dispatch missed timing event
						dispatchTimingWindowResult(false, true, false, window->second);
						m_openWindows.erase(window);
					}
				}
				else if (window->second.m_closeOnWrongInput)
				{
					//dispatch missed timing event
					dispatchTimingWindowResult(false, true, false, window->second);
					m_openWindows.erase(window);
				}
			}
			for (auto window = m_openWindows.begin(); window != m_openWindows.end();)
			{
				if (window->second.m_closeOnWrongPlayerInput)
				{
					//dispatch missed timing event
					dispatchTimingWindowResult(false, true, false, window->second);
					window = m_openWindows.erase(window);
				}
				else
				{
					++window;
				}
			}
			/*if (m_openWindows.empty())
			{
				unregisterInputHandler();
			}*/
		}
		else
		{
			LOG_ERROR("Tried to process an event marked as input Event that was not actually an input event");
		}
	}
	return false;
}

void TimedInputController::openTimingWindow(const Input::PlayerInput player, const InputTimingWindow& window)
{
	m_openWindows[player] = window;
	registerInputHandler();
}
void TimedInputController::openTimingWindow(const Input::PlayerInput player, const Input::InputAction action, const TimingWindow& window, const unsigned int windowID)
{
	//m_openWindows[player] = InputTimingWindow()
}
void TimedInputController::openTimingWindow(const Input::PlayerInput player, const Input::InputAction action, const sf::Time& windowOpen, const sf::Time& windowClose,
	const bool closeOnMissedTime, const bool closeOnWrongInput, const bool closeOnWrongPlayerInput, const bool closeOnWindowHit, const unsigned int windowID)
{
	InputTimingWindow window;
	window.m_window.setWindow(windowOpen, windowClose);
	window.m_onActions.insert(action);
	window.m_closeOnHitTiming = closeOnWindowHit;
	window.m_closeOnMissedTiming = closeOnMissedTime;
	window.m_closeOnWrongInput = closeOnWrongInput;
	window.m_closeOnWrongPlayerInput = closeOnWrongPlayerInput;
	window.m_timingWindowID = windowID;

	m_openWindows[player] = window;
	registerInputHandler();
}

void TimedInputController::clearWindows()
{
	m_openWindows.clear();
	unregisterInputHandler();
}

void TimedInputController::clearPlayerWindow(const Input::PlayerInput player)
{
	if (m_openWindows.empty())
	{
		unregisterInputHandler();
	}
}

void TimedInputController::registerInputHandler()
{
	if (!m_inputEventHookedUp && m_engine)
	{
		m_engine->getEventManager().addListener(fastdelegate::MakeDelegate(this, &TimedInputController::handleInput), InputActionEvent::m_eventSignature);
		m_inputEventHookedUp = true;
	}
}
void TimedInputController::unregisterInputHandler()
{
	if (m_inputEventHookedUp && m_engine)
	{
		m_engine->getEventManager().removeListener(fastdelegate::MakeDelegate(this, &TimedInputController::handleInput), InputActionEvent::m_eventSignature);
		m_inputEventHookedUp = false;
	}
}

void TimedInputController::dispatchTimingWindowResult(const bool hitTiming, const bool missedTiming, const bool expiredTiming, InputTimingWindow& timingWindow)
{
	if (m_engine)
	{
		auto twindowEv = boost::make_shared<TimingWindowEvent>(timingWindow.m_timingWindowID, hitTiming, expiredTiming, missedTiming, timingWindow.m_window);
		m_engine->getEventManager().queueEvent(twindowEv);
	}
}