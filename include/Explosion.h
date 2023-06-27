#pragma once
#include "Macros.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>


class Explosion: public GameObject
{
public:
    Explosion(const sf::Vector2f& position, float radiusLimit);

    void update() override;

    bool isFinished() const;

    void draw(sf::RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const override {
        window->draw(*m_shape);
    }
    float getLimitRadius() const { return m_radiusLimit; }

private:
    float m_radiusLimit;
};
