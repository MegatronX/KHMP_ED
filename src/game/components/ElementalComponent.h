#pragma once
#ifndef _ELEMENTALCOMPONENT_H_

#include <component/component.h>
#include <elements/Elements.h>
namespace KHMP
{
	class ElementalComponent : public Component
	{
	public:
		const static ComponentType m_componentType = 0x63ec402d;
		ElementalComponent(Entity* owner, ComponentID cmpID, const float mod = 0.f, const float floor = -3.f, const float ceil = 3.f);

		bool addElement(const Elements::Element ele, const float value, const bool abs = false, const bool absRelativeToAll = false);
		bool clearElement(const Elements::Element ele);
		unsigned int getAvailableElements() const;
		bool hasElementAvailable(const Elements::Element ele) const ;
		bool hasAnyElementAvailable() const;
		float getElementalWeight(const Elements::Element ele) const;

		float getModerator() const;
		float getFloor() const;
		float getCeiling() const;

		void setModerator(const float mod);
		void setFloor(const float floor);
		void setCeiling(const float ceil);

		RawClonePtr rawClone() const;

		const boost::unordered_map<Elements::Element, float>& getElementWeights() const;

		float sumAllWeights() const;
		bool moderate(const float modValue);
	protected:
		void multiplyAllBy(const float mul);
		unsigned int m_availableElements;
		boost::unordered_map<Elements::Element, float> m_elementLookup;
		float m_moderator;
		float m_floor;
		float m_ceiling;
	};
}

#endif