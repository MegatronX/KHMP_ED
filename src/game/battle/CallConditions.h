#pragma once
#ifndef _CCOND_H_
#define _CCOND_H_

namespace KHMP
{
	//Call condition for action modifiers
	enum CallCondition
	{
		OutgoingAttack,
		IncomingAttack,
		PartyMemberOutgoingAttack,
		PartyMemberIncomingAttack
	};
}

#endif