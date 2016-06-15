#pragma once
#ifndef _PARTICLESYSTEM_H_
#define _PARTICLESYSTEM_H_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <memory>
#include <array>

#include <graphics/Particle.h>

namespace sf
{
	class RenderWindow;
	class Image;
	class Texture;
}

class ParticleSystem : public sf::Drawable, public sf::NonCopyable
{
public:

protected:
private:
	template <typename Signature>
	struct Function
	{
		Function(std::function<Signature> function, sf::Time timeUntilRemoval)
			: function(std::move(function))
			, timeUntilRemoval(timeUntilRemoval)
			, id(nextId())
			, tracker()
		{
		}

		static unsigned int nextId()
		{
			static unsigned int next = 0;
			return next++;
		}

		std::function<Signature>						function;
		sf::Time										timeUntilRemoval;
		unsigned int									id;
		//std::shared_ptr<detail::AbstractConnectionImpl> tracker; ??
	};
	typedef std::array<sf::Vertex, 4> Quad;

};

#endif