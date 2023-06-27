#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\audio.hpp>
#include "Player.h"

using namespace sf;

class GamePlay
{
public:
	GamePlay(bool play);
	void gameLoop(RenderWindow* window);
private:
	void end(RenderWindow* window,bool lost);
	void drawTime(unsigned int time, sf::RenderWindow& window);
	void openShot(RenderWindow*, Board& board);
	sf::RectangleShape m_backGround;
	sf::Text m_text;
	VolumeButton m_volButton;
};
