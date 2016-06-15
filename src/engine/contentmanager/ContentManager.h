#pragma once
#ifndef _CONTENTMANAGER_H_
#define _CONTENTMANAGER_H_
#include <sfml\System.hpp>
#include <sfml/Graphics.hpp>
#include <boost\filesystem.hpp>
#include <boost/unordered_map.hpp>
#include <boost/noncopyable.hpp>
#include <cache/Cache.h>
class Engine;
class ContentManager
{
public:
	ContentManager(Engine* engine);
	void updateCaches(sf::Time time);
	//boost::shared_ptr<sf::Texture> requestTexture(const std::string &name, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rClass, sf::Uint32 time, std::string extension = ".png", bool forceLoad = false);
	boost::shared_ptr<sf::Texture> requestTextureDirectly(std::string &filename);

	boost::shared_ptr<sf::Texture> requestTileMapTexture(const std::string tileMapName);
	boost::shared_ptr<sf::Font> requestFont(const std::string &fontFile, sf::Uint32 time, const std::string extension = ".ttf");
	//boost::shared_ptr<Graphics::BaseSprite> RequestSprite_(const std::string &name, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rClass, sf::Uint32 time, bool Start = false, std::string extension = ".png");
	//Graphics::animsprite_ptr RequestSprite(const std::string &name, const Cache::GameStyle style, const Cache::World world, const Cache::ResourceClass rClass, const sf::Uint32 time, const bool Start = false, const std::string extension = ".png");
	//Graphics::animsprite_ptr;
	const std::string& getMapDirectory() const;
	const std::string& getShaderDirectory() const;
	const std::string& getHTMLDirectory() const;
	const std::string& getResourcesDirectory() const;
	const std::string& getFontDirectory() const;
protected:
private:
	//primary caches
	TextureCache m_mainTextureCahce;
	BigTextureCache m_mainBigTextureCache;
	FontCache m_mainFontCache;

	//secondary caches
	boost::unordered_map<std::string, TextureCache> m_worldTextureCaches;
	boost::unordered_map<std::string, BigTextureCache> m_worldBigTextureCaches;
	boost::unordered_map<std::string, FontCache> m_worldFontCaches;

	//TextureCache m_mainCache;
	//boost::unordered_map<std::string, TextureCache> m_worldCaches;

	Engine* m_engine;

};

#endif