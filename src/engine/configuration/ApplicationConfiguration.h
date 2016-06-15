#pragma once
#ifndef _APPCONFIG_H_
#define _APPCONFIG_H_

#include <string>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
class ApplicationConfiguration
{
public:
	ApplicationConfiguration();
	ApplicationConfiguration(const std::string& configFile);
	void initConfiguration(const std::string& configFile);

	void writeConfiguration(std::ostream& outStream) const;
	void writeConfiguration(std::string& outputFile, bool makeIfNotAvailable) const;

	void setApplicationSetting(const std::string& key, const std::string& val);

	const std::string& getApplicationSetting(const std::string& setting) const;
	const std::string& getApplicationSetting(const char* setting) const;
	
	bool hasApplicationSetting(const std::string& setting) const;
	bool hasApplicationSetting(const char* setting) const;

	/*template <class T>
	T getApplicationSettingAs(const std::string& setting, T defaultVal) const
	{
		return hasApplicationSetting(setting) ? boost::lexical_cast<T>(getApplicationSetting(setting)) : defaultVal;
	}
	template <class T>
	T getApplicationSettingAs(const char* setting) const
	{
		return boost::lexical_cast<T>(getApplicationSetting(setting));
	}*/
	template <class T>
	T getApplicationSetting(const std::string& setting, const T& defaultVal) const
	{
		return hasApplicationSetting(setting) ? boost::lexical_cast<T>(getApplicationSetting(setting)) : defaultVal;
	}
	template <class T>
	T getApplicationSetting(const char* setting, const T& defaultVal)  const
	{
		return hasApplicationSetting(setting) ? boost::lexical_cast<T>(getApplicationSetting(setting)) : defaultVal;
	}
protected:

private:
	boost::unordered_map<std::string, std::string> m_applicationSettings;
	bool m_inputsSet;
	bool m_reportErrors;
};

#endif