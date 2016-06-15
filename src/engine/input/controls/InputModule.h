#pragma once
#ifndef _INPUTMODULE_H_
#define _INPUTMODULE_H_
#include <boost/unordered_map.hpp>
#include <sfml/Window.hpp>
#include <sfml/System.hpp>

//namespace GameEngine
//{
class Engine;
//}

namespace Input
{
	enum PlayerInput
	{
		P1Input = 0,
		P2Input = 1,
		P3Input = 2,
		P4Input = 3,
		Invalid
	};
#define InputCount 12
#define MaxPlayerCount 2
	enum InputAction
	{
		Confirm,
		Cancel,
		Aux1,
		Aux2,
		Start,
		Select,
		Up,
		Down,
		Left,
		Right,
		AuxLeft,
		AuxRight,
		MouseLeft,
		MouseRight,
		MouseMove,
		InvalidAction
	};
	extern const boost::unordered_map<InputAction, std::string> ActionNameLookup;
	extern const boost::unordered_map<std::string, InputAction> NameActionLookup;
	extern const boost::unordered_map<std::string, sf::Keyboard::Key> StringToKeyMap;
	extern const boost::unordered_map<sf::Keyboard::Key, std::string> KeyToStringMap;
	extern const boost::unordered_map<sf::Event::EventType, InputAction> EventTypeToAction;
	extern const boost::unordered_map<InputAction, sf::Event::EventType> ActionToEventType;
	struct InputActionResult
	{
	public:
		InputActionResult(bool cancelled = false, PlayerInput pInput = PlayerInput::P1Input, InputAction iAction = InputAction::InvalidAction) :
			m_cancelled(cancelled), m_IAction(iAction), m_pInput(pInput)
		{

		}
		virtual ~InputActionResult()
		{
		}
		bool m_cancelled;
		InputAction m_IAction;
		PlayerInput m_pInput;
	};
	class PlayerInputSet
	{
	public:
		PlayerInputSet(unsigned int joystckId = 0);
		void mapKeyboardInput(sf::Keyboard::Key key, InputAction action);

		void mapJoystickButton(unsigned int button, InputAction action);

		const boost::unordered_map<sf::Keyboard::Key, InputAction>& getKeyboardInputMap() const;
		const boost::unordered_map<InputAction, sf::Keyboard::Key>& getReverseKeyboardInputMap() const;
		const boost::unordered_map<unsigned int, InputAction>& getJoypadInputMap() const;
		const boost::unordered_map<InputAction, unsigned int>& getReverseJoypadInputMap() const;

		//Returns the key mapped to an action
		sf::Keyboard::Key operator[] (const InputAction action) const;

		//Maps a keyboard key to his players action
		InputAction operator[] (const sf::Keyboard::Key key) const;
		//Return joystick mapping
		InputAction operator[] (const unsigned int joyButton) const;
		unsigned int getJoystickMapping(const InputAction action) const;
		unsigned int getJoystickID() const;

		void clear();
		virtual ~PlayerInputSet();
		//unsigned int operator[] (const sf::Joystick::);
	private:
		boost::unordered_map<sf::Keyboard::Key, InputAction> m_keyboardInputMap;
		boost::unordered_map<InputAction, sf::Keyboard::Key> m_reverseKeyboardInputMap;
		boost::unordered_map<unsigned int, InputAction> m_joypadInputMap;
		boost::unordered_map<InputAction, unsigned int> m_reverseJoypadInputMap;
		unsigned int m_joystickID;

	};

	class InputModule;

	//typedef boost::signals2::signal<void (const sf::Uint32, const InputModule*, InputActionResult& actionResult) > KeyChangeEvent;
	class InputModule
	{
	public:
		InputModule();
		InputModule(const std::string& configFile, Engine* engine);

		void load(const std::string& configFile, Engine* engine);

		PlayerInputSet& getPlayerInput(PlayerInput input);

		bool isActionPushed(PlayerInput input, const InputAction action);
		/*
		boost::signals2::connection addKeyPressedEvent(const KeyChangeEvent::slot_type& handler);
		void dispatchKeyPressedEvents(const sf::Uint32 time, sf::Event::KeyEvent& keyEvent, bool DispatchInvalidActions = false);
		void dispatchJoystickKeyPressedEvents(const sf::Uint32 time, sf::Event::JoystickButtonEvent& joyEvent, bool DispatchInvalidActions = false);

		boost::signals2::connection addKeyReleasedEvent(const KeyChangeEvent::slot_type& handler);
		void dispatchKeyReleasedEvents(const sf::Uint32 time, sf::Event::KeyEvent& keyEvent, bool DispatchInvalidActions = false);
		void dispatchJoystickKeyReleasedEvents(const sf::Uint32 time, sf::Event::JoystickButtonEvent& joyEvent, bool DispatchInvalidActions = false);
		*/
		void setActivePlayer(PlayerInput player);
		PlayerInput getActivePlayer() const;

		void clear();

		void suspendInputs(const sf::Time expireTime, bool timeIsDelta = false);

		void setCurrentEvent(sf::Event& ev);
		const sf::Event& getCurrentEvent() const;

		bool operator[] (const InputAction action);
		bool operator[] (const sf::Keyboard::Key key);
		bool operator[] (unsigned int joystickKey);

	protected:
	private:
		sf::Event* m_currentEvent;
		//sf::Keyboard* keyboard;
		//sf::Joystick* joystick;
		Engine* m_engine;
		bool m_suspended;
		sf::Time m_suspenstionEnd;

		PlayerInput m_activeInput;
		PlayerInputSet m_player1InputMap;
#if MaxPlayerCount > 1
		PlayerInputSet m_player2InputMap;
#endif
#if MaxPlayerCount > 2
		PlayerInputSet m_player3InputMap;
#endif
	};
}
#endif