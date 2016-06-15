#pragma once
#ifndef _CACHE_H_
#define _CACHE_H_
#include <vector>
#include <list>
#include <sstream>
#include <boost\unordered_map.hpp>
#include <boost\unordered_set.hpp>
#include <boost\smart_ptr.hpp>
#include <boost\assign.hpp>
#include <sfml\System.hpp>
#include <sfml\Graphics.hpp>
#include <log/Log.h>
#include <graphics/BigTexture.h>



template <class T>
class TimerCache
{
public:
	typedef boost::shared_ptr<T> res_ptr;
	typedef std::pair<sf::Time, res_ptr > Resource;
	typedef boost::unordered_set<std::string> ResourceIndexSet;
	typedef boost::unordered_map<std::string, Resource> ResourceMap;


	TimerCache(int maxEntries = 100, sf::Time DefaultLifeTime = sf::seconds(300), sf::Time updatetime = sf::milliseconds(1000), res_ptr fallbackresource = res_ptr())
	{
		this->m_maxEntries = maxEntries;
		this->m_resourceLifeTime = DefaultLifeTime;
		this->m_updateTime = updatetime;
		this->m_defaultResource = fallbackresource;
	}

	virtual void update(sf::Time time)
	{
		if (time - m_lastUpdate > m_updateTime)
		{
			m_lastUpdate = time;
			updateCache(time);
		}
	}
	virtual res_ptr requestResource(const std::string &indexer, sf::Time time, bool& resourceFound, const std::string& = ".png", bool forceLoad = false)
	{
		std::string filePath;

		if (!filePath.empty())
		{
			//res_ptr texture = boost::make_shared<sf::Texture>();
			//texture->loadFromFile(filePath);
			Resource textureResource;
			textureResource.first = time + m_resourceLifeTime;
			textureResource.second = boost::make_shared<T>();
			if (!textureResource.second->loadFromFile(filePath))
			{
				LOG_ERROR("Couldn't open texture file " << indexer << std::endl);
				return getFallBack();
			}
			else
			{
				m_resources[indexer] = textureResource;

			}
		}
	}

	virtual void setResourceRoot(const std::string& root)
	{
		m_resourceRoot = root;
	}
protected:
	void updateCache(sf::Time time)
	{
		for (auto Resource = m_resources.begin(); Resource != m_resources.end(); ++Resource)
		{
			sf::Time expireTime = (*Resource).second.first;
			if ((*Resource).second.first < time)
			{
				ResourceIndexSet::iterator res = m_resourceSet.find((*Resource).first);
				if (res != m_resourceSet.end())
					m_resourceSet.erase(res);
				Resource = m_resources.erase(Resource);
				if (Resource == m_resources.end())
					break;
			}
		}
	}
	res_ptr getFallBack()
	{
		return m_defaultResource;
	}

	sf::Time m_resourceLifeTime;
	sf::Time m_updateTime;
	sf::Time m_lastUpdate;
	unsigned int m_maxEntries;
	unsigned int m_currentEntries;
	res_ptr m_defaultResource;
	ResourceIndexSet m_resourceSet;
	ResourceMap m_resources;
	std::string m_resourceRoot;
	//GameStyle CurrentGameStyle;
};

//template specializations
template <>
TimerCache<sf::Texture>::res_ptr TimerCache<sf::Texture>::requestResource(const std::string &indexer, sf::Time time, bool& resourceFound, const std::string& ext, bool forceLoad)
{
	std::string filePath;
	filePath = m_resourceRoot + "\\" + indexer + ext;
	if (!filePath.empty())
	{
		//res_ptr texture = boost::make_shared<sf::Texture>();
		//texture->loadFromFile(filePath);
		Resource textureResource;
		textureResource.first = time + m_resourceLifeTime;
		textureResource.second = boost::make_shared<sf::Texture>();
		if (!textureResource.second->loadFromFile(filePath))
		{
			LOG_ERROR("Couldn't open texture file " << indexer << std::endl);
			return getFallBack();
		}
		else
		{
			m_resources[indexer] = textureResource;

		}
	}
}

template <>
TimerCache<BigTexture>::res_ptr TimerCache<BigTexture>::requestResource(const std::string &indexer, sf::Time time, bool& resourceFound, const std::string& ext, bool forceLoad)
{
	std::string filePath;
	filePath = m_resourceRoot + "\\" + indexer + ext;
	if (!filePath.empty())
	{
		//res_ptr texture = boost::make_shared<sf::Texture>();
		//texture->loadFromFile(filePath);
		Resource textureResource;
		textureResource.first = time + m_resourceLifeTime;
		textureResource.second = boost::make_shared<BigTexture>();
		if (!textureResource.second->loadFromFile(filePath))
		{
			LOG_ERROR("Couldn't open texture file " << indexer << std::endl);
			resourceFound = false;
			return getFallBack();
		}
		else
		{
			m_resources[indexer] = textureResource;
			resourceFound = true;
		}
	}
}

template <>
TimerCache<sf::Font>::res_ptr TimerCache<sf::Font>::requestResource(const std::string &indexer, sf::Time time, bool& resourceFound, const std::string& ext, bool forceLoad)
{
	std::string filePath;
	filePath = m_resourceRoot + "\\" + indexer + ext;
	if (!filePath.empty())
	{
		//res_ptr texture = boost::make_shared<sf::Texture>();
		//texture->loadFromFile(filePath);
		Resource textureResource;
		textureResource.first = time + m_resourceLifeTime;
		textureResource.second = boost::make_shared<sf::Font>();
		if (!textureResource.second->loadFromFile(filePath))
		{
			LOG_ERROR("Couldn't open font file " << indexer << std::endl);
			resourceFound = false;
			return getFallBack();
		}
		else
		{
			m_resources[indexer] = textureResource;
			resourceFound = true;
		}
	}
}

typedef TimerCache<sf::Texture> TextureCache;
typedef TimerCache<BigTexture> BigTextureCache;
typedef TimerCache<sf::Font> FontCache;

#endif