#pragma once
#ifndef _IANIMATEDDRAW_H_
#define _IANIMATEDDRAW_H_

#include <graphics/IDrawable.h>

class IAnimatedDraw : public IDrawable
{
public:
	virtual void update(const sf::Time& time) = 0;
};

#endif