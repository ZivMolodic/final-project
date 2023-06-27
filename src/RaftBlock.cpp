#include "RaftBlock.h"
#include "Explosion.h"

RaftBlock::RaftBlock(const Vector2f& size, const sf::Vector2f& position, const std::string& str)
: GameObject(size, position, str), m_durability(150)
{
	m_durabilityText.setFont(Resources::instance().getFont());
	m_durabilityText.setCharacterSize(20);
	m_durabilityText.setFillColor(sf::Color::Black);
	m_durabilityText.setOutlineThickness(1);
	m_durabilityText.setOutlineColor(sf::Color::White);
}

void RaftBlock::draw(sf::RenderWindow* window, const sf::Vector2f& position) const
{
	window->draw(*m_shape);
	window->draw(m_durabilityText);
}


void RaftBlock::update()
{
	m_durabilityText.setString(std::to_string(m_durability));
	m_durabilityText.setPosition(this->getRectangle().getPosition() + sf::Vector2f(this->getRectangle().getSize().x / 2 - m_durabilityText.getLocalBounds().width / 2, this->getRectangle().getSize().y / 2 - m_durabilityText.getLocalBounds().height / 2));
}

void RaftBlock::handleExplosion(const Explosion& explosion)
{
	auto vec = this->getPosition() - explosion.getPosition();
	m_durability -= EXPLOSION_FACTOR / std::sqrtf(vec.x * vec.x + vec.y * vec.y);
}

