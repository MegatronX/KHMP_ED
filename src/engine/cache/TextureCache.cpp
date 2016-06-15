#include <cache/TextureCache.h>
#include <boost/make_shared.hpp>
#include <log/Log.h>
TextureCache::res_ptr TextureCache::requestResource(const std::string &indexer, sf::Time time, bool& validResource, const std::string& ext, bool forceLoad)
{
	std::string filePath;

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
/*TextureCache::res_ptr TextureCache::requestBigTexture(const std::string &indexer, sf::Time time, bool& resourceFound, const std::string& ext, bool forceLoad)
{
}*/