#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "GameObject.h"

class Explosion;

class RaftBlock: public GameObject
{
public:
	RaftBlock(const Vector2f& size, const sf::Vector2f& position, const std::string& str);
	void draw(sf::RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const override;
	void update() override;
	virtual sf::RectangleShape getRectangle() const = 0;
	void handleExplosion(const Explosion& explosion);
	
private:
	int m_durability;
	sf::Text m_durabilityText;
};

class DownRaft : public RaftBlock
{
public:
	DownRaft(const Vector2f& position)
		:RaftBlock(Vector2f{ 160, 70 }, position, "raft") {}
	sf::RectangleShape getRectangle() const override
	{
		auto rec = sf::RectangleShape({ 160, 20 });
		rec.setPosition(getPosition().x - 80, getPosition().y - 10);
		return rec;
	}
};

class UpRaft : public RaftBlock
{
public:
	UpRaft(const Vector2f& position)
		:RaftBlock(Vector2f{ 160, 120 }, position, "up_raft1") {}
	sf::RectangleShape getRectangle() const override
	{
		auto rec = sf::RectangleShape({ 160, 20 });
		rec.setPosition(getPosition().x - 80, getPosition().y - 40);
		return rec;
	}
};