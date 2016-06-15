#include "BattleCharacterComponent.h"

namespace KHMP
{
	BattleCharacterComponent::BattleCharacterComponent(Entity* owner, ComponentID id) : Component(owner, m_componentType, id), m_timerValue(0), m_overflowRatio(0.f), m_rawOverflow(0)
	{
		/*auto ch = owner->getComponent<BaseCharacterComponent*>(BaseCharacterComponent::m_UID);
		if (ch != nullptr)
		{
			m_ownerCharacter = ch;
			m_inBattleStats = ch->getFinalStats()
		}*/
	}
	void BattleCharacterComponent::handleBattleTick(const ev_ptr& eventData)
	{

	}
	void BattleCharacterComponent::handleCharacterStatChange(const ev_ptr& eventData)
	{

	}
}