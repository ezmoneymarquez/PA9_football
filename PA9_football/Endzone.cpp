#include "Endzone.hpp"

Endzone::Endzone(const sf::Vector2f& position, const sf::Vector2f& size)
{
	area.setPosition(position);
	area.setSize(size);
	area.setFillColor(sf::Color::Blue);
	area.setOutlineColor(sf::Color::White);
	area.setOutlineThickness(2.f);
}

bool Endzone::checkTD(const Player& player) const
{
	return area.getGlobalBounds().findIntersection(player.getBounds()).has_value();
}

void Endzone::draw(sf::RenderWindow& window) const
{
	window.draw(area);
}