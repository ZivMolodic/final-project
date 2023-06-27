#pragma once
#include "SFML/Graphics.hpp"
#include "PhysicsBehavior.h"
#include "Resources.h"
#include "Explosion.h"
#include "GameObject.h"
#include "Animation.h"

// Represents a projectile object with a specified position, destination, and properties.
// Handles collision, updates, and rendering of the objectile.
// Provides functionality for explosion, settling, retrieving the objectile, and velocity control
class Objectile: public DynamicObject, public std::enable_shared_from_this<Objectile>
{
public:
    Objectile(float radius, const sf::Vector2f& position, const sf::Vector2f& destination, const std::string& str, float explosionRadius, float timeBound, bool rotaion = false);
    virtual ~Objectile() = default;
    virtual void handleCollision(const RectangleShape& rec) = 0;
    virtual void update() override;
    void draw(sf::RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const override;
    bool setteled() const;
    std::shared_ptr<GameObject> getObjectile();
    bool explodes() const;
    sf::Vector2f getVelocity() { return m_physics->getVelocity(); }
    void rotate(float rotation) { if (m_enableRotation) m_physics->rotate(rotation); }
protected:
    sf::Clock m_timer;
    void explode() { Resources::instance().playMusic(EXPLOSION, 30);
        m_explosion = std::make_shared<Explosion>(getPosition(), m_explosionRadius);}
private:
    void launch(const Vector2f& velocity) { m_physics->setVelocity(velocity); }
    bool m_enableRotation;
    float m_explosionRadius;
    float m_timeBound;
    std::shared_ptr<Explosion> m_explosion;
};


class Grenade : public Objectile
{
public:
    Grenade(const sf::Vector2f& position, const sf::Vector2f& destination) : Objectile(15, position, destination, "grenade", 150.f, 3.f) {}
    void handleCollision(const RectangleShape& rec) override;
};

class Tennis : public Objectile
{
public:
    Tennis(const sf::Vector2f& position, const sf::Vector2f& destination) : Objectile(10, position, destination, "tennis", 0, 6.f) {}
    void handleCollision(const RectangleShape& rec) override;
    float getFlightTime() { return m_timer.getElapsedTime().asSeconds(); }
};

class Missile : public Objectile
{
public:
    Missile(const sf::Vector2f& position, const sf::Vector2f& destination)
        : Objectile(25, position, destination, "missile", 150.f, 6.f) {}
    void handleCollision(const RectangleShape& rec) override;
    virtual void update() override {
        Objectile::update();
    }
};

class GuidedMissile : public Objectile
{
public:
    GuidedMissile(const sf::Vector2f& position, const sf::Vector2f& destination);
    void handleCollision(const RectangleShape& rec) override;
    virtual void update() override { Objectile::update();
    }
};
