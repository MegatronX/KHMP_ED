#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class Particle
{
public:
	explicit Particle(sf::Time lifeTime);
	sf::Vector2f				m_position;			
	sf::Vector2f				m_velocity;
	float						m_rotation;
	float						m_rotationSpeed;
	sf::Vector2f				m_scale;
	sf::Color					m_color;
	unsigned int				m_textureIndex;
	sf::Time					m_passedLifetime;		// Time passed since emitted.
	sf::Time					m_totalLifetime;		// Total time to live.

	sf::Time getElapsedLifetime();
	sf::Time getTotalLifetime();
	sf::Time getRemainingLifetime();
	float getElapsedRatio();
	float getRemainingRatio();
	void abandonParticle();
protected:
private:

};



#endif