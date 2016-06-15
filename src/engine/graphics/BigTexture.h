/**
Partially borrowed from THOR
**/
#pragma once
#ifndef _BIGTEXTURE_H_
#define _BIGTEXTURE_H_

#include <vector>
#include <string>
#include <sfml/graphics/Texture.hpp>

namespace sf
{
	class Sprite;
}

class BigTexture
{
public:
	BigTexture();

	bool loadFromImage(const sf::Image& image);
	bool loadFromFile(const std::string& fileName);
	bool loadFromMemory(const void* memData, std::size_t dataSize);
	bool loadFromStream(sf::InputStream& inStream);

	sf::Vector2u getSize() const;

	void setSmooth(const bool smooth = true);
	bool isSmooth() const;

private:
	void swap(BigTexture& otherTexture);

	sf::Vector2f fillSprites(const sf::Color& color, std::vector<sf::Sprite>& out) const;

	std::vector<sf::Texture>	mTextures;
	sf::Vector2u				mTableSize;
	sf::Vector2u				mPixelSize;
	bool						mSmooth;

	friend class BigSprite;
};

#endif