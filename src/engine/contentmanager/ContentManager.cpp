#include <contentmanager/ContentManager.h>

ContentManager::ContentManager(Engine* engine) : m_engine(engine)
{

}
void ContentManager::updateCaches(sf::Time time)
{
	m_mainTextureCahce.update(time);
	m_mainBigTextureCache.update(time);
	m_mainFontCache.update(time);

	for (auto cache = m_worldTextureCaches.begin(); cache != m_worldTextureCaches.end(); ++cache)
	{
		(*cache).second.update(time);
	}
	for (auto cache = m_worldBigTextureCaches.begin(); cache != m_worldBigTextureCaches.end(); ++cache)
	{
		(*cache).second.update(time);
	}
	for (auto cache = m_worldFontCaches.begin(); cache != m_worldFontCaches.end(); ++cache)
	{
		(*cache).second.update(time);
	}
}
//boost::shared_ptr<sf::Texture> requestTexture(const std::string &name, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rClass, sf::Uint32 time, std::string extension = ".png", bool forceLoad = false);
boost::shared_ptr<sf::Texture> ContentManager::requestTextureDirectly(std::string &filename)
{

}


boost::shared_ptr<sf::Font> ContentManager::requestFont(const std::string &fontFile, sf::Uint32 time, const std::string extension)
{

}