#include <events/StatusEffectAddedEvent.h>

namespace KHMP
{
	StatusEffectAddedEvent::StatusEffectAddedEvent(boost::shared_ptr<Entity> se, Entity* target, sf::Time time) : IEvent(m_eventSignature, time), m_se(se), m_target(target)
	{

	}

	entity_ptr StatusEffectAddedEvent::getStatusEffect()
	{
		return m_se;
	}
	Entity* StatusEffectAddedEvent::getTarget()
	{
		return m_target;
	}

	StatusEffectAddedEvent::RawClonePtr StatusEffectAddedEvent::rawClone() const
	{
		return RawClonePtr(new StatusEffectAddedEvent(*this));
	}
}