#include "Collisions.hpp"

bool Collisions::intersects(const sf::FloatRect& a, const sf::FloatRect& b)
{
	return a.findIntersection(b).has_value();
}

sf::Vector2f Collisions::getCenter(const sf::FloatRect& rect)
{
	return { rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f };
}