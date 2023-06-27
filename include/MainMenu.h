#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include "Button.h"

// Represents the main menu of the game.
// Manages the menu loop and contains buttons, background, and volume controls.
class MainMenu {
public:
	MainMenu();
	~MainMenu() = default;
	void menuLoop(const sf::Vector2f& size);
private:
	sf::Texture m_logoTexture;
	sf::RectangleShape m_logo;
	std::vector<std::unique_ptr<MainMenuButton>>  m_buttons;
	sf::RectangleShape m_backGround;
	VolumeButton m_volButton;
};