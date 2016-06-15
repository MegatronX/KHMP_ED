#include "BigTexture.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

#include <cassert>
#include <algorithm>

// Maps a 2D index pair to a 1D index
template <typename T>
T& at(std::vector<T>& vector, unsigned int x, unsigned int y, sf::Vector2u tableSize)
{
	return vector[y * tableSize.x + x];
}

template <typename T>
const T& at(const std::vector<T>& vector, unsigned int x, unsigned int y, sf::Vector2u tableSize)
{
	return vector[y * tableSize.x + x];
}

BigTexture::BigTexture()
	: mTextures()
	, mTableSize(0u, 0u)
	, mPixelSize(0u, 0u)
	, mSmooth(false)
{
}

bool BigTexture::loadFromImage(const sf::Image& source)
{
	// Rollback semantics: In case of failure, *this remains unchanged
	BigTexture tmp;

	const unsigned int maxSize = sf::Texture::getMaximumSize();
	tmp.mPixelSize = source.getSize();

	// Number of textures needed, in X and Y direction
	tmp.mTableSize.x = (tmp.mPixelSize.x - 1u) / maxSize + 1u;
	tmp.mTableSize.y = (tmp.mPixelSize.y - 1u) / maxSize + 1u;

	tmp.mTextures.clear();
	tmp.mTextures.reserve(tmp.mTableSize.x * tmp.mTableSize.y);

	// Create sf::Textures that form together the big texture
	for (unsigned int y = 0u; y < tmp.mPixelSize.y; y += maxSize)
	{
		for (unsigned int x = 0u; x < tmp.mPixelSize.x; x += maxSize)
		{
			// Note: sf::Texture::loadFromImage() reduces the rectangle size if necessary
			tmp.mTextures.push_back(sf::Texture());
			if (!tmp.mTextures.back().loadFromImage(source, sf::IntRect(x, y, maxSize, maxSize)))
				return false;
		}
	}

	// Apply smooth filter
	tmp.setSmooth(isSmooth());

	// Success: Commit modifications
	swap(tmp);
	return true;
}

bool BigTexture::loadFromFile(const std::string& filename)
{
	sf::Image image;
	return image.loadFromFile(filename) && loadFromImage(image);
}

bool BigTexture::loadFromMemory(const void* data, std::size_t size)
{
	sf::Image image;
	return image.loadFromMemory(data, size) && loadFromImage(image);
}

bool BigTexture::loadFromStream(sf::InputStream& stream)
{
	sf::Image image;
	return image.loadFromStream(stream) && loadFromImage(image);
}

sf::Vector2u BigTexture::getSize() const
{
	return mPixelSize;
}

void BigTexture::setSmooth(bool smooth)
{
	if (mSmooth != smooth)
	{
		mSmooth = smooth;
		for (auto&& texture : mTextures)
		{
			texture.setSmooth(smooth);
		}
	}
}

bool BigTexture::isSmooth() const
{
	return mSmooth;
}

void BigTexture::swap(BigTexture& other)
{
	std::swap(mTextures, other.mTextures);
	std::swap(mTableSize, other.mTableSize);
	std::swap(mPixelSize, other.mPixelSize);
	std::swap(mSmooth, other.mSmooth);
}

sf::Vector2f BigTexture::fillSprites(const sf::Color& color, std::vector<sf::Sprite>& out) const
{
	const unsigned int maxSize = sf::Texture::getMaximumSize();

	out.clear();
	out.resize(mTextures.size());

	// Add 1 sf::Sprite for every sf::Texture, and connect it
	for (unsigned int i = 0u; i < mTableSize.x; ++i)
	{
		for (unsigned int j = 0u; j < mTableSize.y; ++j)
		{
			const sf::Texture& texture = at(mTextures, i, j, mTableSize);
			sf::Sprite&	       sprite = at(out, i, j, mTableSize);

			sprite.setColor(color);
			sprite.setTexture(texture);
			sprite.setPosition(static_cast<float>(i * maxSize), static_cast<float>(j * maxSize));
		}
	}

	return sf::Vector2f(mPixelSize);
}