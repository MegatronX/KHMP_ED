#pragma once
#ifndef _PROPERTYMANAGER_H_
#define _PROPERTYMANAGER_H_

#include <boost/unordered_map.hpp>

class PropertyManager
{
public:
	void addProperty(const std::string& index, const std::string& value);
	bool hasProperty(const std::string& propName) const;
	bool removeProperty(const std::string& propName);
	const std::string& getProperty(const std::string& propName);
	virtual ~PropertyManager();
protected:
	boost::unordered_map<std::string, std::string> m_properties;
	static std::string emptyString;
};

#endif