#pragma once

#include <memory>
#include "SFML/Graphics.hpp"
#include "Objectile.h"
#include "Resources.h"
#include "RaftBlock.h"
#include "GameObject.h"

// Represents a weapon in the game.
// Manages the size, firing status, shooting, updating, drawing, handling collisions, and explosions of the weapon.
// Provides functions for shooting projectiles, obtaining the current objectile, getting the objectile position, and rotating the weapo
class Weapon: public DynamicObject
{
public:
	Weapon(const sf::Vector2f& size ,const std::string& str);
	virtual ~Weapon() = default;
	bool firing() const { return m_objectile != nullptr; }
	void shot(const sf::Vector2f& destination, const sf::Vector2f& position = sf::Vector2f());
	void update() override;
	virtual void draw(RenderWindow* window, const sf::Vector2f& position) const override;
	std::shared_ptr<GameObject> getObjectile() { if (m_objectile) return m_objectile->getObjectile(); }
	sf::Vector2f getObjectilePosition() { if (m_objectile) return m_objectile->getPosition(); }
	void handleCollision(const RectangleShape& rec) override { if (m_objectile) m_objectile->handleCollision(rec); }
	void rotate(float rotation) { if (m_objectile) m_objectile->rotate(rotation); }
	bool explodes() { if (m_objectile) return m_objectile->explodes(); return false; }
protected:
	virtual void drawAim(sf::RenderWindow* window, float angle, const sf::Vector2f& mousePosition) const;

private:
	virtual std::shared_ptr<Objectile> createObjectile(const sf::Vector2f& launchPosition, const sf::Vector2f& destination) = 0;
	std::shared_ptr<Objectile> m_objectile;
	int m_ammo;
};

class GrenadeLauncher : public Weapon
{
public:
	GrenadeLauncher(): Weapon({ 55.f, 25.f }, "grenade_launcher") {}
private:
	std::shared_ptr<Objectile> createObjectile(const sf::Vector2f& launchPosition, const sf::Vector2f& destination) override
	{
		Resources::instance().playMusic(Sounds::SHOOT, 30);
		// Create a GrenadeObject specific to GrenadeLauncher
		return std::make_shared<Grenade>(launchPosition, destination);
	}
};

class TennisGun : public Weapon
{
public:
	TennisGun() : Weapon({ 25.f, 25.f }, "tennis_gun") {}
private:
	std::shared_ptr<Objectile> createObjectile(const sf::Vector2f& launchPosition, const sf::Vector2f& destination) override
	{
		// Create a GrenadeObject specific to GrenadeLauncher
		return std::make_shared<Tennis>(launchPosition, destination);
	}
};

class MissileLauncher : public Weapon
{
public:
	MissileLauncher() : Weapon({ 55.f, 25.f }, "missile_launcher") {}
private:
	std::shared_ptr<Objectile> createObjectile(const sf::Vector2f& launchPosition, const sf::Vector2f& destination) override
	{
		// Create a GrenadeObject specific to GrenadeLauncher
		return std::make_shared<Missile>(launchPosition, destination);
	}
};

class Remote : public Weapon
{
public:
	Remote() : Weapon({ 15.f, 25.f }, "remote") {}

private:
	virtual void drawAim(sf::RenderWindow* window, float angle, const sf::Vector2f& mousePosition) const {}
	std::shared_ptr<Objectile> createObjectile(const sf::Vector2f& launchPosition, const sf::Vector2f& destination) override
	{
		// Create a GrenadeObject specific to GrenadeLauncher
		return std::make_shared<GuidedMissile>(launchPosition, destination);
	}
};

