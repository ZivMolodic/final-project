#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Resources.h"
#include "Macros.h"
#include <memory>
#include <vector>

using namespace sf;
using namespace std;

class Button
{
public:
	Button(Vector2f position, Vector2f size, const std::string& str, bool play = true);
	~Button() = default;
	FloatRect globalBounds() const { return m_picture.getGlobalBounds(); }
	virtual void draw(RenderWindow* window, sf::Vector2f cursorLocation); 
protected:
	bool m_playing;
	RectangleShape m_picture;
};

class VolumeButton : public Button
{
public:
	VolumeButton(Vector2f position, bool play)
		:Button(position, Vector2f(60, 60),"volume", play), m_playing(play)
	{
		m_playing = play;
		if (!play)
			m_picture.setTexture(&Resources::instance().getTexture("mute"));
	}
	~VolumeButton() = default;
	void play(){
		if (m_playing)
		{
			Resources::instance().volumeBackGround(0);
			m_playing = false;
			m_picture.setTexture(&Resources::instance().getTexture("mute"));
		}
		else
		{
			Resources::instance().volumeBackGround(50);
			m_playing = true;
			m_picture.setTexture(&Resources::instance().getTexture("volume"));
		}
	}
private:
	bool m_playing;
};



class MainMenuButton : public Button
{
public:
	MainMenuButton(Vector2f position)
		:Button(position, Vector2f{ 300, 70 }, "menuBlock"), m_text("", Resources::instance().getFont()) {
		m_text.setPosition(position);
		m_text.setCharacterSize(50);
		m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height / 2.f);
		m_text.setFillColor(sf::Color::White);
		m_text.setOutlineThickness(4);
		m_text.setOutlineColor(sf::Color::Black);
	}
	~MainMenuButton() = default;
	virtual int getNum() const { return 4; }
	void draw(RenderWindow* window, sf::Vector2f cursorLocation) override
	{
		Button::draw(window, cursorLocation);
		window->draw(m_text);
	}
	virtual void play(RenderWindow* window) = 0;
protected:
	sf::Text m_text;
};

class PlayButton : public MainMenuButton
{
public:
	PlayButton(Vector2f position)
		:MainMenuButton(position) 
	{
		m_text.setString("PLAY");
		m_text.setOrigin(Vector2f{ m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f + 10.f });
	}
	~PlayButton() = default;
	void play(RenderWindow* window) override;
};


class NumberButton : public MainMenuButton {
public:
	NumberButton(Vector2f position, int num)
		:MainMenuButton(position), m_num(num)
	{
		m_text.setString(std::to_string(num));
		m_text.setOrigin(Vector2f{ m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f + 10.f });
	}
	~NumberButton() = default;
	void play(RenderWindow* window) override {};
	int getNum() const override { return m_num; }
private:
	int m_num;
};

//class ChoosePlayersButton : public MainMenuButton
//{
//public:
//	ChoosePlayersButton(Vector2f position)
//		:MainMenuButton(position)
//	{
//		float y = BUTTONS_POSITION.y;
//		float spaceBetweenButton = (WINDOW_SIZE.y - SPACE_WITHOUT_BUTTONS * 2.f) / (5 - 1);
//		m_buttons.push_back(std::make_unique<NumberButton>(Vector2f{ BUTTONS_POSITION.x , y }, 4));
//		y += spaceBetweenButton;
//		m_buttons.push_back(std::make_unique<NumberButton>(Vector2f{ BUTTONS_POSITION.x , y }, 5));
//		y += spaceBetweenButton;
//		m_buttons.push_back(std::make_unique<NumberButton>(Vector2f{ BUTTONS_POSITION.x , y }, 6));
//		y += spaceBetweenButton;
//		m_buttons.push_back(std::make_unique<NumberButton>(Vector2f{ BUTTONS_POSITION.x , y }, 7));
//		y += spaceBetweenButton;
//		m_buttons.push_back(std::make_unique<NumberButton>(Vector2f{ BUTTONS_POSITION.x , y }, 8));
//	
//		m_text.setString("PLAYERS");
//		m_text.setOrigin(Vector2f{ m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f + 10.f });
//		m_backGround.setTexture(&Resources::instance().getTexture("main_background"));
//		m_backGround.setSize(WINDOW_SIZE);
//	}
//	~ChoosePlayersButton() = default;
//	void play(RenderWindow* window) override;
//private:
//	std::vector<std::unique_ptr<MainMenuButton>> m_buttons;
//	sf::RectangleShape m_backGround;
//};


class HelpButton : public MainMenuButton
{
public:
	HelpButton(Vector2f position)
		:MainMenuButton(position) 
	{
		m_text.setString("HELP");
		m_text.setOrigin(Vector2f{ m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f + 10.f });
	}
	~HelpButton() = default;

	void play(RenderWindow* window) override;
};


class ExitButton : public MainMenuButton
{
public:
	ExitButton(Vector2f position)
		:MainMenuButton(position)
	{
		m_text.setString("EXIT");
		m_text.setOrigin(Vector2f{ m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f + 10.f });
	}
	~ExitButton() = default;
	void play(RenderWindow* window) override { window->close(); };
};


class GameMenuButton : public Button
{
public:
	GameMenuButton(Vector2f position, const std::string& str)
		:Button(position, Vector2f{ 80, 80 }, str) {}
	virtual enum Menu choose() = 0;
};


class UpRaftButton : public GameMenuButton
{
public:
	UpRaftButton(Vector2f position)
		:GameMenuButton(position, "up_raft_button") {}
	enum Menu choose() override { return UP_RAFT; } 
};

class DownRaftButton : public GameMenuButton
{
public:
	DownRaftButton(Vector2f position)
		:GameMenuButton(position, "down_raft_button") {}
	enum Menu choose() override { return DOWN_RAFT; } 
};

class GrenadeButton : public GameMenuButton
{
public:
	GrenadeButton(Vector2f position)
		:GameMenuButton(position, "grenade_button") {}
	enum Menu choose() override { return GRENADE; } 
};

class TennisButton : public GameMenuButton
{
public:
	TennisButton(Vector2f position)
		:GameMenuButton(position, "tennis_button") {}
	enum Menu choose() override { return TENNIS; } 
};

class MissileButton : public GameMenuButton
{
public:
	MissileButton(Vector2f position)
		:GameMenuButton(position, "missile_button") {}
	enum Menu choose() override { return MISSILE; }
};

class GuidedMissileButton : public GameMenuButton
{
public:
	GuidedMissileButton(Vector2f position)
		:GameMenuButton(position, "guided_missile_button") {}
	enum Menu choose() override { return GUIDED_MISSILE; }
};