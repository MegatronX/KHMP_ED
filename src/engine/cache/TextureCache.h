#pragma once
#ifndef _TEXTURECACHE_H_
#define _TEXTURECACHE_H_
#include <cache\Cache.h>
#include <sfml\Graphics.hpp>
#include <sstream>
#include <string>

class TextureCache : public TimerCache < sf::Texture >
{
public:
	res_ptr requestResource(const std::string &indexer, sf::Time time, bool& resourceFound, const std::string& ext = ".png", bool forceLoad = false) override;
	//res_ptr RequestResource(const std::string &indexer, GameStyle styl, World world, ResourceClass resClass, sf::Uint32 time, sf::Uint32 lifeTime = 0, bool AsCopy = false, const std::string extention = ".png", bool forceLoad = false);
	//res_ptr requestBigTexture(const std::string &indexer, sf::Time time, bool& resourceFound, const std::string& ext = ".png", bool forceLoad = false);
protected:

};

#endif