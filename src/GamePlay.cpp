#include "GamePlay.h"
#include "Resources.h"
#include "Macros.h"
#include <SFML/audio.hpp>



GamePlay::GamePlay(bool play)
    :m_volButton(Vector2f{ WINDOW_SIZE.x - 60, 60 }, play)
{
    m_backGround.setTexture(&Resources::instance().getTexture("gameplay_background"));
    m_backGround.setSize(BACKGROUND_SIZE);
    m_backGround.setPosition({ 0,0 });

    
    m_text.setFont(Resources::instance().getFont());
    m_text.setCharacterSize(50);
    m_text.setPosition(WINDOW_SIZE.x / 2.f, 30);
}

void GamePlay::gameLoop(RenderWindow* window)
{
    auto board = Board(Vector2f{ 220, 400 }, Vector2f{ BACKGROUND_SIZE.x - WINDOW_SIZE.x/2 ,400 }, 4);

    bool playerTurn = true;

    auto view = sf::View(sf::FloatRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));

    int timeAsSeconds = 30;

    window->setFramerateLimit(60);

    //openShot(window, board);

    sf::Clock turnTimer;

    bool firstTime = true;

    while (window->isOpen())
    {
        window->clear();
        window->setView(view);
        window->draw(m_backGround);
        //drawTime(timeAsSeconds-turnTimer.getElapsedTime().asSeconds(), *window);
        //update
        board.update();
        board.handleCollisions();
        board.draw(window);
        m_volButton.draw(window, sf::Vector2f({ sf::Mouse::getPosition(*window).x * 1.f,
                                                sf::Mouse::getPosition(*window).y * 1.f }));
        window->display();

        if (!board.isPlaying())
        {
            if (board.userDead())
                end(window, true);
            else end(window, false);
                break;
        }

        auto event = sf::Event{};
        while (window->pollEvent(event))
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

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (m_volButton.globalBounds().contains(sf::Vector2f({ sf::Mouse::getPosition(*window).x * 1.f,
                                                sf::Mouse::getPosition(*window).y * 1.f })))
                        m_volButton.play();
                }
                break;
            }
            }
        }

        //if (turnTimer.getElapsedTime().asSeconds() >= timeAsSeconds)
        //{
        //    playerTurn = !playerTurn;
        //    turnTimer.restart();
        //}


        board.play(window, event);

        sf::Vector2f position = board.getViewPosition();
        if (position.x - view.getSize().x / 2.f < 0)
            view.setCenter({ view.getSize().x / 2.f , view.getCenter().y });
        else if (position.x + view.getSize().x / 2.f > BACKGROUND_SIZE.x)
            view.setCenter({ BACKGROUND_SIZE.x - view.getSize().x / 2.f , view.getCenter().y });
        else
            view.setCenter(board.getViewPosition().x, view.getCenter().y);
    }
}


void GamePlay::openShot(RenderWindow* window, Board& board)
{
    auto view = sf::View(sf::FloatRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));

    bool firstTime = true;
    bool initTime = false;
    
    sf::Clock timer;

    while (window->isOpen())
    {
        window->clear();
        window->setView(view);
        window->draw(m_backGround);
        board.update();
        board.handleCollisions();
        board.draw(window);
        window->display();
        if (firstTime) {
            sleep(sf::seconds(1));
            firstTime = false;
        }
        view = window->getView();
        if (view.getCenter().x + view.getSize().x / 2.f < m_backGround.getSize().x &&
            view.getCenter().x + view.getSize().x / 2.f > 0)
            view.move(Vector2f({ 1, 0 }) * 10.f);
        else if (!initTime)
        {
            initTime = true;
            timer.restart();
        }
        else if (timer.getElapsedTime().asSeconds() > 1)
            break;
    }
}

void GamePlay::drawTime(unsigned int time, sf::RenderWindow& window)
{
    int min = (time / 60), sec = (time % 60);

    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineThickness(4);
    m_text.setOutlineColor(sf::Color::Black);
   // m_text.setPosition(Vector2f{ window.getView().getCenter().x, window.getView().getCenter().y});
    if (min < 10 && sec < 10)
        m_text.setString("0" + std::to_string(min) + ":0" + (std::to_string(sec)));
    else if (min < 10)
        m_text.setString("0" + std::to_string(min) + ":" + (std::to_string(sec)));
    else if (sec < 10)
        m_text.setString(std::to_string(min) + ":0" + (std::to_string(sec)));
    else
        m_text.setString(std::to_string(min) + ":" + (std::to_string(sec)));

    if (min == 0 && sec <= 10)
    {
        m_text.setFillColor(sf::Color::Red);
    }
    m_text.setOrigin(m_text.getLocalBounds().width / 2.f,
        m_text.getLocalBounds().height / 2.f);
    window.draw(m_text);
}

void GamePlay::end(RenderWindow* window, bool lost)
{
    sf::RectangleShape shape(WINDOW_SIZE);
    if (lost)
    {
        shape.setTexture(&Resources::instance().getTexture("lose"));
        Resources::instance().playMusic(Sounds::GAME_OVER);
    }
    else
    {
        shape.setTexture(&Resources::instance().getTexture("win"));
        Resources::instance().playMusic(Sounds::FINISH_LEVEL);

    }
    Resources::instance().volumeBackGround(0);
    shape.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);
    shape.setOrigin(shape.getSize() / 2.f);
    
    window->clear();
    window->draw(shape);
    window->display();
    sf::sleep(sf::seconds(3));
    Resources::instance().volumeBackGround(50);
}
