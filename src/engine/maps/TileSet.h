#pragma once
#ifndef _TILESET_H_
#define _TILESET_H_

#include <graphics/BigTexture.h>
#include <graphics/BigSprite.h>
#include <boost/shared_ptr.hpp>
class TileSet
{
public:
	TileSet();
	TileSet(const std::string& name, const int firstGID);
	TileSet(const std::string& name, const int firstGID, const unsigned int tileWidth, const unsigned int tileHeight, const std::string& textureFile);
	//Warning: This copies the tile potentially hurting performance
	TileSet(const std::string& name, const int firstGID, const unsigned int tileWidth, const unsigned int tileHeight, const BigTexture& textureFile);

	virtual int getFirstGID();
	virtual int getLastGID();

	sf::Sprite& getTile(int index);
	std::string getName();

	//const sf::Texture& getTexture();
	void setTexture(sf::Texture& image);

	void setTexture(boost::shared_ptr<sf::Texture>& tex);

	void add(sf::Sprite &sprite);

	bool isAnimated() const;

	virtual ~TileSet(void);
protected:
	void processTexture();
	BigTexture m_refTexture;
	std::string m_tileSetName;

	std::vector<BigSprite> tilesprites;
	std::vector<BigSprite>* activetiles;

	int m_firstGID;
	int m_lastGID;
	int m_tileWidth;
	int m_tileHeight;

	//std::vector<sf::Sprite> m_tileSprites;
	std::vector<sf::IntRect> m_tileRects;

	bool m_animated;
};

typedef boost::shared_ptr<TileSet> tileset_ptr;

#endif