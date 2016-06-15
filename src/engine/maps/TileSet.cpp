#include "TileSet.h"
#include <iostream>
TileSet::TileSet()
{

}
TileSet::TileSet(const std::string& name, const int firstGID) : m_tileSetName(name), m_firstGID(firstGID)
{

}
TileSet::TileSet(const std::string& name, const int firstGID, const unsigned int tileWidth, const unsigned int tileHeight, const std::string& textureFile) :
m_tileSetName(name), m_firstGID(firstGID), m_tileWidth(tileWidth), m_tileHeight(tileHeight)
{
	bool loaded = m_refTexture.loadFromFile(textureFile);
	if (loaded)
	{
		processTexture();
	}
	else
	{
		
	}
}

TileSet::TileSet(const std::string& name, const int firstGID, const unsigned int tileWidth, const unsigned int tileHeight, const BigTexture& texture) :
m_tileSetName(name), m_firstGID(firstGID), m_tileWidth(tileWidth), m_tileHeight(tileHeight), m_refTexture(texture)
{
	processTexture();
}

TileSet::~TileSet(void)
{

}

void TileSet::processTexture()
{
	auto size = m_refTexture.getSize();
	int XTiles = (int)size.x / m_tileWidth;
	int YTiles = (int)size.y / m_tileHeight;
	for (int y = 0; y < YTiles; ++y)
	{
		for (int x = 0; x < XTiles; ++x)
		{
			BigSprite sprite(m_refTexture);
			sprite.setTextureRect(sf::IntRect(x * m_tileWidth, y * m_tileHeight, m_tileWidth, m_tileHeight));
			tilesprites.push_back(sprite);
			//sprite.setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
		}
	}
}

int TileSet::getFirstGID()
{
	return m_firstGID;
}
int TileSet::getLastGID()
{
	return m_lastGID;
}
sf::Sprite emptySprite;
sf::Sprite& TileSet::getTile(int index)
{
	return emptySprite;
}
std::string TileSet::getName()
{
	return m_tileSetName;
}

//const sf::Texture& TileSet::getTexture()
//{

//}
void TileSet::setTexture(sf::Texture& image)
{

}

void TileSet::setTexture(boost::shared_ptr<sf::Texture>& tex)
{

}

void TileSet::add(sf::Sprite &sprite)
{

}

bool TileSet::isAnimated() const
{
	return false;
}

