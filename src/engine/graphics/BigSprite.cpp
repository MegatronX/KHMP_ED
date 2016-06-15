#include <iostream>
#include <log/Log.h>
#include "BigSprite.h"
#include "BigTexture.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

BigSprite::BigSprite()
	: sf::Drawable()
	, sf::Transformable()
	, mSize(0.f, 0.f)
	, mSplitSprites()
	, mColor(sf::Color::White)
{
}

BigSprite::BigSprite(const BigTexture& texture)
: sf::Drawable(), sf::Transformable(), mSize(), mSplitSprites(), mColor(sf::Color::White), m_actualSpriteSet(false)
{
	setTexture(texture);
}

void BigSprite::setTexture(const BigTexture& texture)
{
	mSize = texture.fillSprites(mColor, mSplitSprites);
}

void BigSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (m_actualSpriteSet)
	{
		for (auto&& sprite : m_actualSprites)
		{
			target.draw(sprite);
		}
	}
	else
	{
		for (auto&& sprite : mSplitSprites)
		{
			target.draw(sprite, states);
		}
	}
}

void BigSprite::setColor(const sf::Color& color)
{
	mColor = color;
	if (m_actualSpriteSet)
	{
		for (auto&& sprite : m_actualSprites)
		{
			sprite.setColor(color);
		}
	}
	for (auto&& sprite : mSplitSprites)
	{
		sprite.setColor(color);
	}
	//AURORA_FOREACH(sf::Sprite& sprite, mSplitSprites)
	//	sprite.setColor(color);
}

sf::Color BigSprite::getColor() const
{
	return mColor;
}
void BigSprite::setTextureRect(sf::IntRect& rect)
{
	int x = rect.left;
	int y = rect.top;
	int width = rect.width;
	int height = rect.height;
	int runningx = 0;
	int runningy = 0;
	m_actualSprites.clear();
	const unsigned int maxSize = sf::Texture::getMaximumSize();
	//int spritesInX = 
	for (unsigned int i = 0; i < mSplitSprites.size(); ++i)
	{
		auto size = mSplitSprites[i].getTexture()->getSize();
		int xbound = runningx + size.x;
		int ybound = runningy + size.y;
		if ((x < xbound && x >= runningx) && (y < ybound && y >= runningy))
		{
			int runOverX = (x + width) - xbound;
			int runOverY = (y + height) - ybound;
			if ((runOverX > 0) && (runOverY > 0))
			{
				LOG_DEBUG("No implementation for sprite splitting at x, y split");
			}
			else if (runOverX > 0)
			{
				LOG_DEBUG("No implementation for sprite splitting at x");
			}
			else if (runOverY > 0)
			{
				LOG_DEBUG("No implementation for sprite splitting at y");
			}
			else
			{
				m_actualSprites.push_back(sf::Sprite());
				m_actualSprites[0].setTexture(*(mSplitSprites[i].getTexture()));
				m_actualSprites[0].setTextureRect(sf::IntRect(x - runningx, y - runningy, width, height));

			}
			break;
		}
		runningx += size.x;
		//if (runningx > )
	}
}
sf::FloatRect BigSprite::getLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, mSize.x, mSize.y);
}

sf::FloatRect BigSprite::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}