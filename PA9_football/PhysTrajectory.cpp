#include "PhysTrajectory.hpp"

void PhysTrajectory::applyLinear(sf::Vector2f& position, sf::Vector2f& velocity, float dt)
{
	position += velocity * dt;
}

void PhysTrajectory::applyFriction(sf::Vector2f& velocity, float friction)
{
	velocity *= friction;
	if (std::abs(velocity.x) < 0.01f)
		velocity.x = 0.f;
	if (std::abs(velocity.y) < 0.01f)
		velocity.y = 0.0f;
}

void PhysTrajectory::applyGravity(sf::Vector2f& velocity, float gravity, float dt)
{
	velocity.y += gravity * dt;
}