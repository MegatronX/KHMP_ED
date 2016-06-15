#include <events/ActionProcessedEvent.h>

namespace KHMP
{
	ActionProcessedEvent::ActionProcessedEvent(Action* action, Entity* target, BattleField* field, Mechanics* mechanics, sf::Time time) :
		IEvent(m_eventSignature, time), m_processedAction(action), m_originalTarget(target)/*, m_finalTarget(finalTarget)*/, m_field(field), m_mechanics(mechanics)
	{

	}

	/*Entity* ActionProcessedEvent::getOriginalTarget() const
	{
		return m_originalTarget;
	}*/
	Entity* ActionProcessedEvent::getTarget() const
	{
		return m_originalTarget;
	}
	Action* ActionProcessedEvent::getAction() const
	{
		return m_processedAction;
	}
}