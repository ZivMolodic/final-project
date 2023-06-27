#include "Explosion.h"

Explosion::Explosion(const sf::Vector2f& position, float radiusLimit)
    : GameObject(0, position, "explosion"), m_radiusLimit(radiusLimit)
{}

void Explosion::update()
{
    CircleShape* circle = dynamic_cast<CircleShape*>(m_shape.get());
    if (circle)
    {
        if (auto radius = circle->getRadius(); radius < m_radiusLimit) {
            circle->setRadius(radius + 25.f);
            circle->setOrigin(radius, radius);
        }
        else
            setDead();
    }
}

bool Explosion::isFinished() const
{
    if (dynamic_cast<CircleShape*>(m_shape.get())->getRadius() >= m_radiusLimit)
        return true;
    else
        return false;
}