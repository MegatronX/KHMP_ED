#include <numeric>
#include <utility>
#include <components/ElementalComponent.h>

namespace KHMP
{
	ElementalComponent::ElementalComponent(Entity* owner, ComponentID cmpID, const float mod, const float floor, const float ceil) 
		: Component(owner, m_componentType, cmpID), m_moderator(mod), m_floor(floor), m_ceiling(ceil)
	{

	}

	bool ElementalComponent::addElement(const Elements::Element ele, const float value, const bool abs, const bool absRelativeToAll)
	{
		// != m_elementLookup.end() ? m_elementLookup[ele] : 0.f;
		bool changed = false;
		if (value != 0.f)
		{
			auto it = m_elementLookup.find(ele);
			if (it != m_elementLookup.end())
			{
				float newVal = 0.f;
				if (absRelativeToAll)
				{
					float sum = sumAllWeights();
					if (sum > 0.f)
						newVal = (value * sum) / (1 - value);
					else
						newVal = value;
				}
				else
				{
					newVal = abs ? value : (m_elementLookup[ele] + value);
					//abs ? value : (m_elementLookup[ele] + value);
				}
				if (newVal < 0.001f && newVal > -0.001f)
				{
					m_elementLookup.erase(it);
					m_availableElements &= ~(ele);
					changed = true;
				}
				else if (m_elementLookup[ele] != newVal)
				{
					changed = true;
					m_elementLookup[ele] = newVal;// abs ? value : (m_elementLookup[ele] + value);
				}
			}
			else
			{
				m_elementLookup[ele] = value;
				m_availableElements |= (static_cast<unsigned int>(ele));
				changed = true;
			}
		}
		return changed;
	}
	bool ElementalComponent::clearElement(const Elements::Element ele)
	{
		bool removed = false;
		auto it = m_elementLookup.find(ele);
		if (it != m_elementLookup.end())
		{
			m_elementLookup.erase(it);
			m_availableElements &= ~(ele);
			removed = true;
		}
		return removed;
	}
	unsigned int ElementalComponent::getAvailableElements() const
	{
		return m_availableElements;
	}
	bool ElementalComponent::hasElementAvailable(const Elements::Element ele) const
	{
		return (m_availableElements & (static_cast<unsigned int>(ele))) != 0;
	}
	bool ElementalComponent::hasAnyElementAvailable() const
	{
		return m_availableElements > 0;
	}

	float ElementalComponent::getElementalWeight(const Elements::Element ele) const
	{
		float weight = m_moderator;
		auto it = m_elementLookup.find(ele);
		if (it != m_elementLookup.end())
		{
			return it->second;
		}
		return weight;
	}

	float ElementalComponent::getModerator() const
	{
		return m_moderator;
	}
	float ElementalComponent::getFloor() const
	{
		return m_floor;
	}
	float ElementalComponent::getCeiling() const
	{
		return m_ceiling;
	}

	void ElementalComponent::setModerator(const float mod)
	{
		m_moderator = mod;
	}
	void ElementalComponent::setFloor(const float floor)
	{
		m_floor = floor;
	}
	void ElementalComponent::setCeiling(const float ceil)
	{
		m_ceiling = ceil;
	}

	const boost::unordered_map<Elements::Element, float>& ElementalComponent::getElementWeights() const
	{
		return m_elementLookup;
	}

	float ElementalComponent::sumAllWeights() const
	{
		return std::accumulate(m_elementLookup.begin(), m_elementLookup.end(), 0.f, 
			[](const float previous, const std::pair<Elements::Element, float>& p) 
		    { 
				 return previous + p.second; 
		   });
	}

	bool ElementalComponent::moderate(const float modValue)
	{
		bool moderated = false;
		if (modValue > 0.f && hasAnyElementAvailable())
		{
			float sum = sumAllWeights();
			if (sum > 0.f)
			{
				multiplyAllBy((1.f) / sum);
				moderated = true;
			}
			
		}
		return moderated;
	}

	ElementalComponent::RawClonePtr ElementalComponent::rawClone() const
	{
		return RawClonePtr(new ElementalComponent(*this));
	}

	void ElementalComponent::multiplyAllBy(const float mul)
	{
		if (hasAnyElementAvailable())
		{
			for (auto ele = m_elementLookup.begin(); ele != m_elementLookup.end(); ++ele)
			{
				ele->second *= mul;
			}
		}
	}
}