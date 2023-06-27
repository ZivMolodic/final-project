#pragma once
#include "GameObject.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class RaftBlock;

// Represents a game board containing player and computer positions, handles game logic, updates, and rendering.
// Manages game objects, player turns, collisions, and tracks time.
class Board
{
public:
	Board(const sf::Vector2f& playerPosition, const sf::Vector2f& computerPosition, int numOfRaftMen);
	void addObject(GameObject* object);
	void update();
	void draw(RenderWindow* window) const;
	void play(RenderWindow* window, const sf::Event& event);
	void handleCollisions();
	sf::Vector2f getUserPosition() const;
	bool shooting() const ;
	sf::Vector2f getObjectilePosition() const;
	sf::Vector2f getViewPosition() const;
	bool isPlaying();
	bool userDead(); 
private:
	bool m_userTurn;
	sf::Vector2f m_userPosition;
	sf::Vector2f m_computerPosition;
	Player m_user;
	Computer m_computer;
	std::vector<GameObject*> m_objects;
	sf::Clock m_turnTime;
};