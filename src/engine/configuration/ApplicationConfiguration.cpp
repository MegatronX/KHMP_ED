#include "ApplicationConfiguration.h"
#include <input/files/xml/pugixml.hpp>

ApplicationConfiguration::ApplicationConfiguration() : m_reportErrors(false), m_inputsSet(false)
{

}
ApplicationConfiguration::ApplicationConfiguration(const std::string& configFile) : m_reportErrors(false), m_inputsSet(false)
{
	using namespace std;
	using namespace pugi;
	xml_document doc;
	m_inputsSet = false;
	if (doc.load_file(configFile.c_str()))
	{
		xml_node configRoot = doc.child("configuration");
		xml_node settings = configRoot.child("appSettings");
		for (xml_node setting = settings.child("add"); setting; setting = setting.next_sibling("add"))
		{
			std::string key, value;
			key = setting.attribute("key").value();
			value = setting.attribute("value").value();
			m_applicationSettings[key] = value;
			//ConfigMappings.[key] = value;
		}
	}
}
void ApplicationConfiguration::initConfiguration(const std::string& configFile)
{
	using namespace std;
	using namespace pugi;
	xml_document doc;
	m_inputsSet = false;
	if (doc.load_file(configFile.c_str()))
	{
		xml_node configRoot = doc.child("configuration");
		xml_node settings = configRoot.child("appSettings");
		for (xml_node setting = settings.child("add"); setting; setting = setting.next_sibling("add"))
		{
			std::string key, value;
			key = setting.attribute("key").value();
			value = setting.attribute("value").value();
			m_applicationSettings[key] = value;
			//ConfigMappings.[key] = value;
		}
	}
}

void ApplicationConfiguration::writeConfiguration(std::ostream& outStream) const
{

}
void ApplicationConfiguration::writeConfiguration(std::string& outputFile, bool makeIfNotAvailable) const
{

}

void ApplicationConfiguration::setApplicationSetting(const std::string& key, const std::string& val)
{
	m_applicationSettings[key] = val;
}

std::string emptyString;
const std::string& ApplicationConfiguration::getApplicationSetting(const std::string& setting) const
{
	auto it = m_applicationSettings.find(setting);
	if (it != m_applicationSettings.end())
	{
		return it->second;
	}
	return emptyString;
}
const std::string& ApplicationConfiguration::getApplicationSetting(const char* setting) const
{
	return getApplicationSetting(std::string(setting));
}

bool ApplicationConfiguration::hasApplicationSetting(const std::string& setting) const
{
	return m_applicationSettings.find(setting) != m_applicationSettings.end();
}
bool ApplicationConfiguration::hasApplicationSetting(const char* setting) const
{
	return hasApplicationSetting(std::string(setting));
}