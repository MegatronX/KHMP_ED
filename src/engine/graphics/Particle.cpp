#include <graphics/Particle.h>

Particle::Particle(sf::Time totalLifetime)
	: m_position(), m_velocity(), m_rotation(), m_rotationSpeed(), m_scale(1.f, 1.f), m_color(255, 255, 255), m_textureIndex(0), m_passedLifetime(sf::Time::Zero), m_totalLifetime(totalLifetime)
{
}

sf::Time Particle::getElapsedLifetime()
{
	return m_passedLifetime;
}
sf::Time Particle::getTotalLifetime()
{
	return m_totalLifetime;
}
sf::Time Particle::getRemainingLifetime()
{
	return m_totalLifetime - m_passedLifetime;
}
float Particle::getElapsedRatio()
{
	return m_passedLifetime / m_totalLifetime;
}
float Particle::getRemainingRatio()
{
	return getRemainingLifetime() / m_passedLifetime;
}
void Particle::abandonParticle()
{
	m_passedLifetime = m_totalLifetime;
}