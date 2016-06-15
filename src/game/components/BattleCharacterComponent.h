#pragma once
#ifndef _BATTLECHARACTERCOMPONENT_H_
#define _BATTLECHARACTERCOMPONENT_H_
#include <array>
#include <vector>
#include <component/Component.h>

#include <events/IEvent.h>
namespace KHMP
{
	enum GenerationType
	{
		REAL,
		SPECULATIVE
	};
	class Mechanics;
	class BattleCharacterComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0x6dfaa5a4;
		BattleCharacterComponent(Entity* owner, ComponentID id);// Mechanics& mechanics);
	protected:
		virtual void handleBattleTick(const ev_ptr& eventData);
		virtual void handleCharacterStatChange(const ev_ptr& eventData);
	private:
		int m_timerValue;
		int m_rawOverflow;
		float m_overflowRatio;
		std::vector<int> m_additionalTimerValues;
		std::vector<int> m_additionalRawOverflows;
		std::vector<float> m_additionalOverflowRatios;
	};
}
#endif
