#pragma once
#ifndef _TIMEDINPUTCONTROLLER_H_
#define _TIMEDINPUTCONTROLLER_H_

#include <boost/unordered_set.hpp>

#include <input/controls/InputReceiver.h>
#include <time/TimingWindow.h>
#include <events/IEvent.h>
struct InputTimingWindow
{
	InputTimingWindow();
	InputTimingWindow(const Input::InputAction& action, const TimingWindow& window, const bool closeOnhittiming = true, const bool closeOnMissedTiming = true,
		const bool closeOnWrongInput = true, const bool closeOnWrontPlayer = false);
	boost::unordered_set<Input::InputAction> m_onActions;
	TimingWindow m_window;
	bool m_closeOnMissedTiming;
	bool m_closeOnWrongInput;
	bool m_closeOnWrongPlayerInput;
	bool m_closeOnHitTiming;
	unsigned int m_timingWindowID; //this is used when you care about a specific window rather than just that a window was hit
};

class TimedInputController : public Input::InputReceiver
{
public:
	TimedInputController(Engine* engine);
	~TimedInputController();
	void update(const sf::Time time);
	virtual bool handleInput(ev_ptr inputEvent) override;

	void openTimingWindow(const Input::PlayerInput player, const InputTimingWindow& window);
	void openTimingWindow(const Input::PlayerInput player, const Input::InputAction action, const TimingWindow& window, const unsigned int windowID = 0);
	void openTimingWindow(const Input::PlayerInput player, const Input::InputAction action, const sf::Time& windowOpen, const sf::Time& windowClose,
		const bool closeOnMissedTime = true, const bool closeOnWrongInput = true, const bool closeOnWrongPlayerInput = false, const bool closeOnWindowHit = true, const unsigned int windowID = 0);

	void clearWindows();
	void clearPlayerWindow(const Input::PlayerInput player);
protected:
	void registerInputHandler();
	void unregisterInputHandler();

	void dispatchTimingWindowResult(const bool hitTiming, const bool missedTiming, const bool expiredTiming, InputTimingWindow& timingWindow);
private:
	boost::unordered_map<Input::PlayerInput, InputTimingWindow> m_openWindows;

	Engine* m_engine;
	bool m_inputEventHookedUp;
};

#endif