#include "InputActionEvent.h"

const EventType InputActionEvent::m_eventSignature = 0x410ac0b6;


InputActionEvent::InputActionEvent(Input::InputAction action, bool pushed, Input::PlayerInput player, Input::InputModule* module, const sf::Time time)
	: m_action(action), m_module(module), m_actionPushed(pushed), IEvent(m_eventSignature, time), m_handled(false)
{

}

/*const EventType& InputActionEvent::getEventType() const
{
	return m_eventSignature;
}*/

/*void InputActionEvent::serialize(std::ostringstream& out) const
{
	out << m_action;
}*/

Input::InputAction InputActionEvent::getAction() const
{
	return m_action;
}
Input::InputModule* InputActionEvent::getInputModule() const
{
	return m_module;
}
Input::PlayerInput InputActionEvent::getPlayer() const
{
	return m_input;
}
bool InputActionEvent::isActionPushed() const
{
	return m_actionPushed;
}

bool InputActionEvent::isHandled() const
{
	return m_handled;
}
void InputActionEvent::setHandled(const bool handled)
{
	m_handled = handled;
}

InputActionEvent::RawClonePtr InputActionEvent::rawClone() const
{
	return new InputActionEvent(*this);
}

/*const std::string& InputActionEvent::getName() const
{
	const static std::string eventName("InputActionEvent");
	return eventName;
}*/
