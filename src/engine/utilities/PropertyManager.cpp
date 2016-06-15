#include "PropertyManager.h"

std::string PropertyManager::emptyString = std::string();

void PropertyManager::addProperty(const std::string& index, const std::string& value)
{
	m_properties[index] = value;
}
bool PropertyManager::hasProperty(const std::string& propName) const
{
	return m_properties.find(propName) != m_properties.end();
}
bool PropertyManager::removeProperty(const std::string& propName)
{
	bool rem = false;

	auto it = m_properties.find(propName);
	if (it != m_properties.end())
	{
		rem = true;
		m_properties.erase(it);
	}

	return rem;
}
const std::string& PropertyManager::getProperty(const std::string& propName)
{
	auto it = m_properties.find(propName);
	if (it != m_properties.end())
	{
		return it->second;
	}
	return emptyString;
}
PropertyManager::~PropertyManager()
{

}