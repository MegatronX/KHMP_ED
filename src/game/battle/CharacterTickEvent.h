#ifndef _CHARACTERTICK_EVENT_H_
#define _CHARACTERTICK_EVENT_H_

#include <events/IEvent.h>
//#include <battle/
namespace KHMP
{

	class CharacterTickEvent : public IEvent
	{
	public:
		static const EventType m_eventSignature;
		CharacterTickEvent(const sf::Uint32 timestamp = 0U);
	protected:
	private:
	};
}

#endif