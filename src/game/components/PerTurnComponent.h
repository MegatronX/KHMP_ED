#pragma once
#ifndef _PERTURNCOMPONENT_H_
#define _PERTURNCOMPONENT_H_

#include <component/Component.h>

namespace KHMP
{
	class PerTurnComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0xfd6950dc;
		PerTurnComponent(Entity* owner, ComponentID id, bool startOfTurn, bool endOfTurn) : Component(owner, m_componentType, id), m_startOfTurn(startOfTurn), m_endOfTurn(endOfTurn)
		{

		}

		bool getAppliesAtStartOfTurn() const
		{
			return m_startOfTurn;
		}
		bool getAppliesAtEndOfTurn() const
		{
			return m_endOfTurn;
		}
	protected:
		bool m_startOfTurn;
		bool m_endOfTurn;
	};
}

#endif