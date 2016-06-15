#pragma once
#ifndef _INPUTActionEVENT_H_
#define _INPUTActionEVENT_H_

#include <events/IEvent.h>
#include <input/controls/InputModule.h>
class InputActionEvent : public IEvent
{
public:
	static const EventType m_eventSignature;

	InputActionEvent(Input::InputAction action, bool pushed, Input::PlayerInput player, Input::InputModule* module, const sf::Time time = sf::Time::Zero);

	//virtual const EventType& getEventType() const override;

	//void serialize(std::ostringstream& out) const override;

	Input::InputAction getAction() const;
	Input::InputModule* getInputModule() const;
	Input::PlayerInput getPlayer() const;

	bool isActionPushed() const;

	bool isHandled() const;
	void setHandled(const bool handled);

	virtual RawClonePtr rawClone() const override;
protected:
private:
	bool m_handled;
	bool m_actionPushed;
	Input::InputAction m_action;
	Input::PlayerInput m_input;
	Input::InputModule* m_module;
};

#endif