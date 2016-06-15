#include "InputModule.h"
#include <boost/assign.hpp>
#include <Engine.h>
#include <input/files/xml/pugixml.hpp>
using namespace sf;
//using namespace GameEngine;
//using namespace Keyboard;
namespace Input
{

	const boost::unordered_map<InputAction, std::string> ActionNameLookup = boost::assign::map_list_of
		(InputAction::Aux1, "Aux1")
		(InputAction::Aux2, "Aux2")
		(InputAction::AuxLeft, "AuxLeft")
		(InputAction::AuxRight, "AuxRight")
		(InputAction::Cancel, "Cancel")
		(InputAction::Confirm, "Confirm")
		(InputAction::Down, "Down")
		(InputAction::InvalidAction, "InvalidAction")
		(InputAction::Left, "Left")
		(InputAction::MouseLeft, "MouseLeft")
		(InputAction::MouseRight, "MouseRight")
		(InputAction::Right, "Right")
		(InputAction::Select, "Select")
		(InputAction::Start, "Start")
		(InputAction::Up, "Up");
	const boost::unordered_map<std::string, InputAction> NameActionLookup = boost::assign::map_list_of
		("Aux1", InputAction::Aux1)
		("Aux2", InputAction::Aux2)
		("AuxLeft", InputAction::AuxLeft)
		("AuxRight", InputAction::AuxRight)
		("Cancel", InputAction::Cancel)
		("Confirm", InputAction::Confirm)
		("Down", InputAction::Down)
		("InvalidAction", InputAction::InvalidAction)
		("Left", InputAction::Left)
		("MouseLeft", InputAction::MouseLeft)
		("MouseRight", InputAction::MouseRight)
		("Right", InputAction::Right)
		("Select", InputAction::Select)
		("Start", InputAction::Start)
		("Up", InputAction::Up);
	const boost::unordered_map<std::string, sf::Keyboard::Key> StringToKeyMap = boost::assign::map_list_of
		("A", sf::Keyboard::A)
		("B", sf::Keyboard::B)
		("C", sf::Keyboard::C)
		("D", sf::Keyboard::D)
		("E", sf::Keyboard::E)
		("F", sf::Keyboard::F)
		("G", sf::Keyboard::G)
		("H", sf::Keyboard::H)
		("I", sf::Keyboard::I)
		("J", sf::Keyboard::J)
		("K", sf::Keyboard::K)
		("L", sf::Keyboard::L)
		("M", sf::Keyboard::M)
		("N", sf::Keyboard::N)
		("O", sf::Keyboard::O)
		("P", sf::Keyboard::P)
		("Q", sf::Keyboard::Q)
		("R", sf::Keyboard::R)
		("S", sf::Keyboard::S)
		("T", sf::Keyboard::T)
		("U", sf::Keyboard::U)
		("V", sf::Keyboard::V)
		("W", sf::Keyboard::W)
		("X", sf::Keyboard::X)
		("Y", sf::Keyboard::Y)
		("Z", sf::Keyboard::Z)
		("Num0", sf::Keyboard::Num0)
		("Num1", sf::Keyboard::Num1)
		("Num2", sf::Keyboard::Num2)
		("Num3", sf::Keyboard::Num3)
		("Num4", sf::Keyboard::Num4)
		("Num5", sf::Keyboard::Num5)
		("Num6", sf::Keyboard::Num6)
		("Num7", sf::Keyboard::Num7)
		("Num8", sf::Keyboard::Num8)
		("Num9", sf::Keyboard::Num9)
		("Escape", sf::Keyboard::Escape)
		("LControl", sf::Keyboard::LControl)
		("LShift", sf::Keyboard::LShift)
		("LAlt", sf::Keyboard::LAlt)
		("LSystem", sf::Keyboard::LSystem)
		("RControl", sf::Keyboard::RControl)
		("RShift", sf::Keyboard::RShift)
		("RAlt", sf::Keyboard::RAlt)
		("RSystem", sf::Keyboard::RSystem)
		("Menu", sf::Keyboard::Menu)
		("LBracket", sf::Keyboard::LBracket)
		("RBracket", sf::Keyboard::RBracket)
		("SemiColon", sf::Keyboard::SemiColon)
		("Comma", sf::Keyboard::Comma)
		("Period", sf::Keyboard::Period)
		("Quote", sf::Keyboard::Quote)
		("Slash", sf::Keyboard::Slash)
		("BackSlash", sf::Keyboard::BackSlash)
		("Tilde", sf::Keyboard::Tilde)
		("Equal", sf::Keyboard::Equal)
		("Dash", sf::Keyboard::Dash)
		("Space", sf::Keyboard::Space)
		("Return", sf::Keyboard::Return)
		("BackSpave", sf::Keyboard::BackSpace)
		("Tab", sf::Keyboard::Tab)
		("PageUp", sf::Keyboard::PageUp)
		("PageDown", sf::Keyboard::PageDown)
		("End", sf::Keyboard::End)
		("Home", sf::Keyboard::Home)
		("Insert", sf::Keyboard::Insert)
		("Delete", sf::Keyboard::Delete)
		("Add", sf::Keyboard::Add)
		("Subtract", sf::Keyboard::Subtract)
		("Multiply", sf::Keyboard::Multiply)
		("Divide", sf::Keyboard::Divide)
		("Left", sf::Keyboard::Left)
		("Right", sf::Keyboard::Right)
		("Up", sf::Keyboard::Up)
		("Down", sf::Keyboard::Down)
		("Numpad0", sf::Keyboard::Numpad0)
		("Numpad1", sf::Keyboard::Numpad1)
		("Numpad2", sf::Keyboard::Numpad2)
		("Numpad3", sf::Keyboard::Numpad3)
		("Numpad4", sf::Keyboard::Numpad4)
		("Numpad5", sf::Keyboard::Numpad5)
		("Numpad6", sf::Keyboard::Numpad6)
		("Numpad7", sf::Keyboard::Numpad7)
		("Numpad8", sf::Keyboard::Numpad8)
		("Numpad9", sf::Keyboard::Numpad9)
		("F1", sf::Keyboard::F1)
		("F2", sf::Keyboard::F2)
		("F3", sf::Keyboard::F3)
		("F4", sf::Keyboard::F4)
		("F5", sf::Keyboard::F5)
		("F6", sf::Keyboard::F6)
		("F7", sf::Keyboard::F7)
		("F8", sf::Keyboard::F8)
		("F9", sf::Keyboard::F9)
		("F10", sf::Keyboard::F10)
		("F11", sf::Keyboard::F11)
		("F12", sf::Keyboard::F12)
		("F13", sf::Keyboard::F13)
		("F14", sf::Keyboard::F14)
		("F15", sf::Keyboard::F15)
		("Pause", sf::Keyboard::Pause)
		("KeyCount", sf::Keyboard::KeyCount)
		;
	const boost::unordered_map<sf::Keyboard::Key, std::string> KeyToStringMap = boost::assign::map_list_of
		(sf::Keyboard::A, "A")
		(sf::Keyboard::B, "B")
		(sf::Keyboard::C, "C")
		(sf::Keyboard::D, "D")
		(sf::Keyboard::E, "E")
		(sf::Keyboard::F, "F")
		(sf::Keyboard::G, "G")
		(sf::Keyboard::H, "H")
		(sf::Keyboard::I, "I")
		(sf::Keyboard::J, "J")
		(sf::Keyboard::K, "K")
		(sf::Keyboard::L, "L")
		(sf::Keyboard::M, "M")
		(sf::Keyboard::N, "N")
		(sf::Keyboard::O, "O")
		(sf::Keyboard::P, "P")
		(sf::Keyboard::Q, "Q")
		(sf::Keyboard::R, "R")
		(sf::Keyboard::S, "S")
		(sf::Keyboard::T, "T")
		(sf::Keyboard::U, "U")
		(sf::Keyboard::V, "V")
		(sf::Keyboard::W, "W")
		(sf::Keyboard::X, "X")
		(sf::Keyboard::Y, "Y")
		(sf::Keyboard::Z, "Z")
		(sf::Keyboard::Num0, "Num0")
		(sf::Keyboard::Num1, "Num1")
		(sf::Keyboard::Num2, "Num2")
		(sf::Keyboard::Num3, "Num3")
		(sf::Keyboard::Num4, "Num4")
		(sf::Keyboard::Num5, "Num5")
		(sf::Keyboard::Num6, "Num6")
		(sf::Keyboard::Num7, "Num7")
		(sf::Keyboard::Num8, "Num8")
		(sf::Keyboard::Num9, "Num9")
		(sf::Keyboard::Escape, "Escape")
		(sf::Keyboard::LControl, "LControl")
		(sf::Keyboard::LShift, "LShift")
		(sf::Keyboard::LAlt, "LAlt")
		(sf::Keyboard::LSystem, "LSystem")
		(sf::Keyboard::RControl, "RControl")
		(sf::Keyboard::RShift, "RShift")
		(sf::Keyboard::RAlt, "RAlt")
		(sf::Keyboard::RSystem, "RSystem")
		(sf::Keyboard::Menu, "Menu")
		(sf::Keyboard::LBracket, "LBracket")
		(sf::Keyboard::RBracket, "RBracket")
		(sf::Keyboard::SemiColon, "SemiColon")
		(sf::Keyboard::Comma, "Comma")
		(sf::Keyboard::Period, "Period")
		(sf::Keyboard::Quote, "Quote")
		(sf::Keyboard::Slash, "Slash")
		(sf::Keyboard::BackSlash, "BackSlash")
		(sf::Keyboard::Tilde, "Tilde")
		(sf::Keyboard::Equal, "Equal")
		(sf::Keyboard::Dash, "Dash")
		(sf::Keyboard::Space, "Space")
		(sf::Keyboard::Return, "Return")
		(sf::Keyboard::BackSpace, "BackSpace")
		(sf::Keyboard::Tab, "Tab")
		(sf::Keyboard::PageUp, "PageUp")
		(sf::Keyboard::PageDown, "PageDown")
		(sf::Keyboard::End, "End")
		(sf::Keyboard::Home, "Home")
		(sf::Keyboard::Insert, "Insert")
		(sf::Keyboard::Delete, "Delete")
		(sf::Keyboard::Add, "Add")
		(sf::Keyboard::Subtract, "Subtract")
		(sf::Keyboard::Multiply, "Multiply")
		(sf::Keyboard::Divide, "Divide")
		(sf::Keyboard::Left, "Left")
		(sf::Keyboard::Right, "Right")
		(sf::Keyboard::Up, "Up")
		(sf::Keyboard::Down, "Down")
		(sf::Keyboard::Numpad0, "Numpad0")
		(sf::Keyboard::Numpad1, "Numpad1")
		(sf::Keyboard::Numpad2, "Numpad2")
		(sf::Keyboard::Numpad3, "Numpad3")
		(sf::Keyboard::Numpad4, "Numpad4")
		(sf::Keyboard::Numpad5, "Numpad5")
		(sf::Keyboard::Numpad6, "Numpad6")
		(sf::Keyboard::Numpad7, "Numpad7")
		(sf::Keyboard::Numpad8, "Numpad8")
		(sf::Keyboard::Numpad9, "Numpad9")
		(sf::Keyboard::F1, "F1")
		(sf::Keyboard::F2, "F2")
		(sf::Keyboard::F3, "F3")
		(sf::Keyboard::F4, "F4")
		(sf::Keyboard::F5, "F5")
		(sf::Keyboard::F6, "F6")
		(sf::Keyboard::F7, "F7")
		(sf::Keyboard::F8, "F8")
		(sf::Keyboard::F9, "F9")
		(sf::Keyboard::F10, "F10")
		(sf::Keyboard::F11, "F11")
		(sf::Keyboard::F12, "F12")
		(sf::Keyboard::F13, "F13")
		(sf::Keyboard::F14, "F14")
		(sf::Keyboard::F15, "F15")
		(sf::Keyboard::Pause, "Pause")
		(sf::Keyboard::KeyCount, "KeyCount")
		;
	const boost::unordered_map<sf::Event::EventType, InputAction> EventTypeToAction = boost::assign::map_list_of
		(sf::Event::MouseMoved, InputAction::MouseMove)
		(sf::Event::MouseButtonPressed, InputAction::MouseLeft);
	const boost::unordered_map<InputAction, sf::Event::EventType> ActionToEventType = boost::assign::map_list_of
		(InputAction::MouseMove, sf::Event::MouseMoved)
		(InputAction::MouseLeft, sf::Event::MouseButtonPressed)
		(InputAction::MouseRight, sf::Event::MouseButtonPressed);
	PlayerInputSet::PlayerInputSet(unsigned int joystckId) : m_joystickID(joystckId)
	{

	}

	void PlayerInputSet::mapKeyboardInput(sf::Keyboard::Key key, InputAction action)
	{
		m_keyboardInputMap[key] = action;
		m_reverseKeyboardInputMap[action] = key;
	}

	void PlayerInputSet::mapJoystickButton(unsigned int button, InputAction action)
	{
		m_joypadInputMap[button] = action;
		m_reverseJoypadInputMap[action] = button;
	}

	PlayerInputSet::~PlayerInputSet()
	{
	}

	const boost::unordered_map<sf::Keyboard::Key, InputAction>& PlayerInputSet::getKeyboardInputMap() const
	{
		return m_keyboardInputMap;
	}
	const boost::unordered_map<InputAction, sf::Keyboard::Key>& PlayerInputSet::getReverseKeyboardInputMap() const
	{
		return m_reverseKeyboardInputMap;
	}
	const boost::unordered_map<unsigned int, InputAction>& PlayerInputSet::getJoypadInputMap() const
	{
		return m_joypadInputMap;
	}
	const boost::unordered_map<InputAction, unsigned int>& PlayerInputSet::getReverseJoypadInputMap() const
	{
		return m_reverseJoypadInputMap;
	}

	//Returns the key mapped to an action
	sf::Keyboard::Key PlayerInputSet::operator[] (const InputAction action) const
	{
		auto it = m_reverseKeyboardInputMap.find(action);
		if (it != m_reverseKeyboardInputMap.end())
		{
			auto ktest = it->second;
			return it->second;
		}
		return sf::Keyboard::Space;
	}
	//Maps a keyboard key to his players action
	InputAction PlayerInputSet::operator[] (const sf::Keyboard::Key key) const
	{
		auto it = m_keyboardInputMap.find(key);
		if (it != m_keyboardInputMap.end())
		{
			return it->second;
		}
		return InputAction::InvalidAction;
	}
	//Return joystick mapping
	InputAction PlayerInputSet::operator[] (const unsigned int joyButton) const
	{
		auto it = m_joypadInputMap.find(joyButton);
		if (it != m_joypadInputMap.end())
			return it->second;
		return InputAction::InvalidAction;
	}
	unsigned int PlayerInputSet::getJoystickMapping(const InputAction action) const
	{
		auto it = m_joypadInputMap.find(action);
		if (it != m_joypadInputMap.end())
			return it->second;
		return -1;
	}
	unsigned int PlayerInputSet::getJoystickID() const
	{
		return m_joystickID;
	}

	void PlayerInputSet::clear()
	{
		m_keyboardInputMap.clear();
		m_reverseKeyboardInputMap.clear();
		m_joypadInputMap.clear();
		m_reverseJoypadInputMap.clear();
	}

	InputModule::InputModule() : m_suspended(false), m_suspenstionEnd(sf::Time::Zero)
	{

	}
	InputModule::InputModule(const std::string& configFile, Engine* engine) : m_engine(engine), m_suspended(false), m_suspenstionEnd(sf::Time::Zero)
	{
		//if (_engine->GetContentManager().VerifyResourceExistance(configFile))
		{
			using namespace std;
			using namespace pugi;
			//InputsSet = false;
			xml_document doc;
			xml_parse_result result = doc.load_file(configFile.c_str());
			if (!result)
				std::cerr << "Configuration Failed To Load. Error: " << result.description();
			else
			{
				xml_node configRoot = doc.child("configuration");
				xml_node settings = configRoot.child("inputConfig");
				for (xml_node pinput = settings.first_child(); pinput; pinput = pinput.next_sibling())
				{
					PlayerInputSet* inputSet = nullptr;
					if (pinput.name() == std::string("Player1"))
					{
						inputSet = &m_player1InputMap;
					}
#if MaxPlayerCount > 1
					else if (pinput.name() == std::string("Player2"))
					{
						inputSet = &m_player2InputMap;
					}
#endif
#if MaxPlayerCount > 2
					else if (pinput->name() == "Player3")
					{
						inputSet = &m_player3InputMap;
					}
#endif
					if (inputSet != nullptr)
					{
						xml_node keyboardNode = pinput.child("keyboard");
						if (keyboardNode != nullptr)
						{
							for (xml_node keypress = keyboardNode.child("add"); keypress; keypress = keypress.next_sibling("add"))
							{
								std::string key, value;
								key = keypress.attribute("key").value();
								value = keypress.attribute("value").value();
								auto it = StringToKeyMap.find(key);
								if (it != StringToKeyMap.end())
								{
									auto it2 = NameActionLookup.find(key);
									if (it2 != NameActionLookup.end())
									{
										inputSet->mapKeyboardInput(it->second, it2->second);
									}
								}
							}
						}
						xml_node joystickNode = pinput.child("joystick");
						if (joystickNode != nullptr)
						{

						}
					}
				}
			}
		}
		//else
		{

		}
	}

	void InputModule::load(const std::string& configFile, Engine* engine)
	{
		this->clear();
		this->m_engine = engine;
		//if (engine->GetContentManager().VerifyResourceExistance(configFile))
		{
			using namespace std;
			using namespace pugi;
			//InputsSet = false;
			xml_document doc;
			xml_parse_result result = doc.load_file(configFile.c_str());
			if (!result)
				std::cerr << "Configuration Failed To Load. Error: " << result.description();
			else
			{
				xml_node configRoot = doc.child("configuration");
				xml_node settings = configRoot.child("inputConfig");
				for (xml_node pinput = settings.first_child(); pinput; pinput = pinput.next_sibling())
				{
					PlayerInputSet* inputSet = nullptr;
					//	std::string inputname = pinput.name();
					if (pinput.name() == std::string("Player1"))
					{
						inputSet = &m_player1InputMap;
					}
#if MaxPlayerCount > 1
					else if (pinput.name() == std::string("Player2"))
					{
						inputSet = &m_player2InputMap;
					}
#endif
#if MaxPlayerCount > 2
					else if (pinput->name() == "Player3")
					{
						inputSet = &m_player3InputMap;
					}
#endif
					if (inputSet != nullptr)
					{
						xml_node keyboardNode = pinput.child("keyboard");
						if (keyboardNode != nullptr)
						{
							for (xml_node keypress = keyboardNode.child("add"); keypress; keypress = keypress.next_sibling("add"))
							{
								std::string key, action;
								key = keypress.attribute("key").value();
								action = keypress.attribute("action").value();
								auto it = StringToKeyMap.find(key);
								if (it != StringToKeyMap.end())
								{
									auto it2 = NameActionLookup.find(action);
									if (it2 != NameActionLookup.end())
									{
										inputSet->mapKeyboardInput(it->second, it2->second);
									}
								}
							}
						}
						xml_node joystickNode = pinput.child("joystick");
						if (joystickNode != nullptr)
						{

						}
					}
				}
			}
		}
		//else
		{

		}
	}

	PlayerInputSet& InputModule::getPlayerInput(PlayerInput input)
	{
		switch (input)
		{
		case PlayerInput::P1Input:
			return m_player1InputMap;
#if MaxPlayerCount > 1
		case PlayerInput::P2Input:
			return m_player2InputMap;
#endif
#if MaxPlayerCount > 2
		case PlayerInput::P3Input:
			return m_player3InputMap;
#endif
		default:
			{
				std::cerr << "Invalid player input selected! Defaulting to player 1\n";
				return m_player1InputMap;
			}
		}
	}

	bool InputModule::isActionPushed(PlayerInput input, const InputAction action)
	{
		PlayerInputSet* set = nullptr;
		switch (input)
		{
		case P1Input:
			set = &m_player1InputMap;
			break;
#if MaxPlayerCount > 1
		case P2Input:
			set = &m_player2InputMap;
			break;
#endif
#if MaxPlayerCount > 2
		case P3Input:
			set = &Player3InputMap;
			break;
#endif

		}
		return set != nullptr &&
			(sf::Keyboard::isKeyPressed((*set)[action]) || sf::Joystick::isButtonPressed((*set).getJoystickID(), (*set).getJoystickMapping(action)));
	}


	/*
	boost::signals2::connection InputModule::addKeyPressedEvent(const KeyChangeEvent::slot_type& handler)
	{
	return _keyPressedSignal.connect(handler);
	}
	void InputModule::dispatchKeyPressedEvents(const sf::Uint32 time, sf::Event::KeyEvent& keyEvent, bool DispatchInvalidActions)
	{
	if (_suspended && time < _suspenstionEnd)
	return;
	else
	{
	_suspended = false;
	_suspenstionEnd = time;
	auto action = _player1InputMap[keyEvent.code];
	if (DispatchInvalidActions || action != InputAction::InvalidAction)
	_keyPressedSignal(time, this, InputActionResult(false, P1Input, action));
	#if MaxPlayerCount > 1
	action = _player2InputMap[keyEvent.code];
	if (DispatchInvalidActions || action != InputAction::InvalidAction)
	_keyPressedSignal(time, this, InputActionResult(false, P2Input, action));
	#endif
	#if MaxPlayerCount > 2
	action = Player3InputMap[keyEvent.Code];
	if (DispatchInvalidActions || action != InputAction::InvalidAction)
	KeyPressedignal(this, InputActionResult(false, P3Input, action));
	#endif
	if (_currentEvent != nullptr)
	{
	auto it = EventTypeToAction.find(_currentEvent->type);
	if (it != EventTypeToAction.end())
	_keyPressedSignal(time, this, InputActionResult(false, P1Input, it->second));
	}

	}
	}
	void InputModule::dispatchJoystickKeyPressedEvents(const sf::Uint32 time, sf::Event::JoystickButtonEvent& joyEvent, bool DispatchInvalidActions)
	{
	if (_suspended)
	return;
	else
	{
	_suspended = false;
	_suspenstionEnd = time;
	switch(joyEvent.joystickId)
	{
	case 0:
	{
	auto action = _player1InputMap[joyEvent.button];
	if (action == InputAction::InvalidAction && !DispatchInvalidActions)
	return;
	_keyPressedSignal(time, this, InputActionResult(false, P1Input, action));
	break;
	}
	#if MaxPlayerCount > 1
	case 1:
	{
	auto action = _player1InputMap[joyEvent.button];
	if (action == InputAction::InvalidAction && !DispatchInvalidActions)
	return;
	_keyPressedSignal(time, this, InputActionResult(false, P2Input, action));
	break;
	}

	#endif
	#if MaxPlayerCount > 2
	case 2:
	break;
	#endif
	}
	}
	}

	boost::signals2::connection InputModule::addKeyReleasedEvent(const KeyChangeEvent::slot_type& handler)
	{
	return _keyReleasedSignal.connect(handler);
	}
	void InputModule::dispatchKeyReleasedEvents(const sf::Uint32 time, sf::Event::KeyEvent& keyEvent, bool DispatchInvalidActions)
	{
	if (_suspended)
	return;
	else
	{

	auto action = _player1InputMap[keyEvent.code];
	if (DispatchInvalidActions || action != InputAction::InvalidAction)
	_keyReleasedSignal(time, this, InputActionResult(false, P1Input, action));
	#if MaxPlayerCount > 1
	action = _player2InputMap[keyEvent.code];
	if (DispatchInvalidActions || action != InputAction::InvalidAction)
	_keyReleasedSignal(time, this, InputActionResult(false, P2Input, action));
	#endif
	#if MaxPlayerCount > 2
	action = Player3InputMap[keyEvent.Code];
	if (DispatchInvalidActions || action != InputAction::InvalidAction)
	KeyReleasedSignal(this, InputActionResult(false, P3Input, action));
	#endif
	if (_currentEvent != nullptr)
	{
	auto it = EventTypeToAction.find(_currentEvent->type);
	if (it != EventTypeToAction.end())
	_keyReleasedSignal(time, this, InputActionResult(false, P1Input, it->second));
	}
	}

	//KeyReleasedSignal(this, )
	}
	void InputModule::dispatchJoystickKeyReleasedEvents(const sf::Uint32 time, sf::Event::JoystickButtonEvent& joyEvent, bool DispatchInvalidActions)
	{
	if (_suspended)
	return;
	else
	{
	switch(joyEvent.joystickId)
	{
	case 0:
	{
	auto action = _player1InputMap[joyEvent.button];
	if (action == InputAction::InvalidAction && !DispatchInvalidActions)
	return;
	_keyReleasedSignal(time, this, InputActionResult(false, P1Input, action));
	break;

	}
	#if MaxPlayerCount > 1
	case 1:
	{
	auto action = _player1InputMap[joyEvent.button];
	if (action == InputAction::InvalidAction && !DispatchInvalidActions)
	return;
	_keyReleasedSignal(time, this, InputActionResult(false, P2Input, action));
	break;

	}
	#endif
	#if MaxPlayerCount > 2
	case 2:
	break;
	#endif
	}
	}
	}
	*/
	void InputModule::setActivePlayer(PlayerInput player)
	{
		m_activeInput = player;
	}
	PlayerInput InputModule::getActivePlayer() const
	{
		return m_activeInput;
	}

	void InputModule::clear()
	{
		m_player1InputMap.clear();
#if MaxPlayerCount > 1
		m_player2InputMap.clear();
#endif
#if MaxPlayerCount > 2
		m_player3InputMap.Clear();
#endif
	}

	void InputModule::suspendInputs(const sf::Time expireTime, bool timeIsDelta)
	{
		if (timeIsDelta)
		{
			m_suspenstionEnd = m_engine->getRealTime() + expireTime;
			m_suspended = true;
		}
		else
		{
			if (expireTime > m_engine->getRealTime())
			{
				m_suspended = true;
				m_suspenstionEnd = expireTime;
			}
		}
	}
	void InputModule::setCurrentEvent(sf::Event& ev)
	{
		m_currentEvent = &ev;
	}
	const sf::Event& InputModule::getCurrentEvent() const
	{
		return *m_currentEvent;
	}
	bool InputModule::operator[] (const InputAction action)
	{
		PlayerInputSet* set = nullptr;
		switch (m_activeInput)
		{
		case P1Input:
			set = &m_player1InputMap;
			break;
#if MaxPlayerCount > 1
		case P2Input:
			set = &m_player2InputMap;
			break;
#endif
#if MaxPlayerCount > 2
		case P3Input:
			set = &Player3InputMap;
			break;
#endif

		}
		return set != nullptr &&
			(sf::Keyboard::isKeyPressed((*set)[action]) || sf::Joystick::isButtonPressed((*set).getJoystickID(), (*set).getJoystickMapping(action)));
		//return keyboard->IsKeyPressed(Player1InputMap[action]) || joystick->IsButtonPressed(Player1InputMap.GetJoystickID(), joystick->)
	}
	bool InputModule::operator[] (const sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}
	bool InputModule::operator[] (unsigned int joystickKey)
	{
		//Implement later
		return false;
	}
}