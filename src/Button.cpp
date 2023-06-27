#include "Button.h"
#include "GamePlay.h"

using namespace sf;

Button::Button(Vector2f position, Vector2f size, const std::string& str, bool play)
    :m_playing(play)
{
	m_picture.setTexture(&Resources::instance().getTexture(str));
	m_picture.setSize(size);
	m_picture.setPosition(position);
	m_picture.setOrigin(m_picture.getSize() / 2.f);
}

void Button::draw(RenderWindow* window, sf::Vector2f cursorLocation)
{ 
	m_picture.setScale(1, 1);

	if (m_picture.getGlobalBounds().contains(cursorLocation))
		m_picture.setScale(1.2, 1.2);

	window->draw(m_picture); 
}


void PlayButton::play(RenderWindow* window)
{
	auto gamePlay = GamePlay(m_playing);
	gamePlay.gameLoop(window, 4);
}

void HelpButton::play(RenderWindow* window)
{
    sf::RectangleShape help(WINDOW_SIZE);
    sf::Texture texture;
    texture.loadFromFile("help.png");
    help.setTexture(&texture);
    help.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);
    help.setOrigin(help.getSize() / 2.f);

    sf::RectangleShape back({ 100, 60 });
    sf::Texture texture1;
    texture1.loadFromFile("back.png");
    back.setTexture(&texture1);
    back.setPosition({ 820, 550 });
    back.setOrigin(back.getSize() / 2.f);

    while (window->isOpen())
    {
        window->clear();
        window->draw(help);
        back.setScale(1, 1);
        if (back.getGlobalBounds().contains(sf::Vector2f({ sf::Mouse::getPosition(*window).x * 1.f,
                                                sf::Mouse::getPosition(*window).y * 1.f })))
            back.setScale(1.2, 1.2);

        window->draw(back);
        window->display();

        if (auto event = sf::Event{}; window->waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window->close();
                break;
            }

            case sf::Event::MouseButtonReleased:
            {
                auto location = window->mapPixelToCoords({ event.mouseButton.x,
                                                           event.mouseButton.y });
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                {
                    if (back.getGlobalBounds().contains(location))
                        return;
                    break;
                }
                }
            }
            }
        }
    }
}

//void ChoosePlayersButton::play(RenderWindow* window)
//{
//    while (window->isOpen())
//    {
//        window->clear();
//        window->draw(m_backGround);
//
//        auto cursorLocation = sf::Vector2f({ sf::Mouse::getPosition(*window).x * 1.f,
//                                                sf::Mouse::getPosition(*window).y * 1.f });
//
//        for (auto const& button : m_buttons)
//            button->draw(window, cursorLocation);
//        
//        window->display();
//
//        for (auto event = sf::Event{}; window->pollEvent(event); )
//        {
//            switch (event.type)
//            {
//            case sf::Event::Closed:
//            {
//                window->close();
//                break;
//            }
//
//            case sf::Event::MouseButtonReleased:
//            {
//
//                switch (event.mouseButton.button)
//                {
//                case sf::Mouse::Left:
//                {
//                    for (auto const& button : m_buttons)
//                        if (button->globalBounds().contains(sf::Vector2f({ sf::Mouse::getPosition(*window).x * 1.f,
//                                                            sf::Mouse::getPosition(*window).y * 1.f })))
//                        {
//                            auto gamePlay = GamePlay();
//                            gamePlay.gameLoop(window, button->getNum());
//                            break;
//                        }
//
//                    break;
//                }
//                }
//            }
//            }
//        }
//    }
//}