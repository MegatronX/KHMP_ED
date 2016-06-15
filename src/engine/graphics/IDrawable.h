#pragma once
#ifndef _IDRAWABLE_H_
#define _IDRAWABLE_H_

#include <sfml/graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class IDrawable : public sf::Drawable, public sf::Transformable
{
public:
	bool isDrawing() const
	{
		return m_draw;
	}

	void setIsDrawing(const bool draw)
	{
		m_draw = draw;
	}

	virtual void setTransparency(const bool transparent = true)
	{
		m_transparent = transparent;
	}
protected:
	bool m_draw;
	bool m_transparent;
private:
};


#endif