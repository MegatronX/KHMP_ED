#pragma once
#ifndef _BIGSPRITE_H_
#define _BIGSPRITE_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

namespace sf
{

	class RenderTarget;
	class RenderStates;

} // namespace sf

class BigTexture;

class BigSprite : public sf::Drawable, public sf::Transformable
{
public:
	BigSprite();
	explicit BigSprite(const BigTexture& texture);

	void setTexture(const BigTexture& texture);

	void setColor(const sf::Color& color);
	sf::Color getColor() const;

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void setTextureRect(sf::IntRect& rect);
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	std::vector<sf::Sprite>		mSplitSprites;
	std::vector<sf::Sprite>		m_actualSprites;
	bool						m_actualSpriteSet;
	sf::Vector2f				mSize;
	sf::Color					mColor;
};

#endif