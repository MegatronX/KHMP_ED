#pragma once
#ifndef _BASECHARACTERCOMPONENT_H_
#define _BASECHARACTERCOMPONENT_H_

#include <Entity/Entity.h>

namespace KHMP
{
	class BaseCharacterComponent : public Component
	{
	public:
		static const ComponentType m_componentType = 0xcafb3ed2;
		BaseCharacterComponent(Entity* owner, ComponentID id);
	protected:
	private:

		int m_characterLevel;
		std::string m_characterName;
		std::string m_displayName;
	};
}

#endif