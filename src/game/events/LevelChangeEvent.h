#pragma once
#ifndef _LEVELCHANGEEVENT_H_
#define _LEVELCHANGEEVENT_H_

#include <events/IEvent.h>
#include <entity/Entity.h>
namespace KHMP
{
	class LevelChangeEvent : public IEvent
	{
	public:
		const static EventType m_eventSignature = 0x55fa1b9;
		LevelChangeEvent(int newLevel, int oldLevel, Entity* character);

		int getNewLevel() const
		{
			return m_newLevel;
		}
		int getOldLevel() const
		{
			return m_oldLevel;
		}
		Entity* getCharacter()
		{
			return m_character;
		}
	protected:

	private:
		Entity* m_character;
		int m_newLevel;
		int m_oldLevel;
	};
}

#endif