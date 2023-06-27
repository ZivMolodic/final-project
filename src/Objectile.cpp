#include "Objectile.h"


Objectile::Objectile(float radius, const sf::Vector2f& position, const sf::Vector2f& destination,
    const std::string& str, float explosionRadius, float timeBound, bool rotation)
    : DynamicObject(radius ,position,str,0.3f,1), m_explosion(nullptr), m_explosionRadius(explosionRadius),
    m_timeBound(timeBound), m_enableRotation(rotation)
{
    m_physics->setBodyToRotate(true);
    launch(destination);
    m_timer.restart();
}

bool Objectile::setteled() const 
{ 
    if (m_explosion) 
        return m_explosion->isFinished(); 
    
    return false; 
}

std::shared_ptr<GameObject> Objectile::getObjectile()
{ 
    if (m_explosion) 
        return m_explosion; 
    else 
        return this->shared_from_this();

}

bool Objectile::explodes() const
{ 
    if (m_explosion) 
        return true; 
    
    return false; 
}

void Objectile::draw(sf::RenderWindow* window, const sf::Vector2f& position ) const
{ 
    if (!m_explosion) 
        window->draw(*m_shape); 
    else 
        m_explosion->draw(window); 
}


GuidedMissile::GuidedMissile(const sf::Vector2f& position, const sf::Vector2f& destination)
: Objectile(30, position, destination, "guided_missile", 150.f, 3.f, true)
{
    m_physics->setGravity(false);
}

void Grenade::handleCollision(const RectangleShape& rec) 
{
    if (m_timer.getElapsedTime().asSeconds() < 0.3f && m_physics->getVelocity().y < 0)
        return;
    if (auto update = m_physics->manageCollision(getPosition(), rec); update != sf::Vector2f(0, 0))
        m_shape->setPosition(update);

    //if (m_physics->getVelocity() == sf::Vector2f(0, 0))
    //    m_setteled = true;
}

void Tennis::handleCollision(const RectangleShape& rec)
{
    if (m_timer.getElapsedTime().asSeconds() < 0.3f && m_physics->getVelocity().y < 0)
        return;
    if (auto update = m_physics->manageCollision(getPosition(), rec); update != sf::Vector2f(0, 0))
        m_shape->setPosition(update);
}

void Missile::handleCollision(const RectangleShape& rec)
{
    if (m_timer.getElapsedTime().asSeconds() < 0.3f && m_physics->getVelocity().y < 0)
        return;
    if (auto update = m_physics->manageCollision(getPosition(), rec); update != sf::Vector2f(0, 0))
        explode();
}

void GuidedMissile::handleCollision(const RectangleShape& rec)
{
    if (m_timer.getElapsedTime().asSeconds() < 0.3f && m_physics->getVelocity().y < 0)
        return;
    if (auto update = m_physics->manageCollision(getPosition(), rec); update != sf::Vector2f(0, 0))
        explode();
}

void Objectile::update()
{
    if (m_explosion)
        m_explosion->update();

    else if (m_timer.getElapsedTime().asSeconds() > m_timeBound)
        explode();
    else
    {
        m_physics->update(m_shape.get());

        //if (m_physics->getVelocity() == sf::Vector2f(0, 0))
        //    m_setteled = true;
    }
}


