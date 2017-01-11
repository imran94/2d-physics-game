#include "Puck.h"
#include <cmath>

Puck::Puck(sf::RenderWindow &w)
{
	velocity = Vector2d(0, 0);
	window = &w;

	sf::Texture* texture = new sf::Texture();
	if (texture->loadFromFile("Assets\\Texture\\Puck.png"))
	{
		std::cout << "File loaded\n";
	}
	else
	{
		std::cout << "File not loaded\n";
	}

	sprite = sf::Sprite(*texture);

	WINDOW_WIDTH = window->getSize().x;
	WINDOW_HEIGHT = window->getSize().y;

	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT / 2;
}

void Puck::setPosition(double x, double y)
{
	sprite.setPosition(x, y);
}

sf::Vector2f Puck::getPosition()
{
	return sprite.getPosition();
}

void Puck::draw()
{
	sprite.setPosition(x - radius, y - radius);
	window->draw(sprite);
}

SoundManager sound;

void Puck::update()
{
	x += velocity.i *= 0.98f;
	y += velocity.j *= 0.98f;

	// Bounce off left wall
	if (x <= radius)
	{
		velocity.i = std::abs(velocity.i);
		x = radius;
		sound.PlayEdgeSound();
	}

	// Bounce off right wall
	if (x >= WINDOW_WIDTH - radius)
	{
		velocity.i = -std::abs(velocity.i);
		x = WINDOW_WIDTH - radius;
		sound.PlayEdgeSound();
	}

	// Bounce off top
	if (y <= radius)
	{
		velocity.j = std::abs(velocity.j);
		y = radius;
		sound.PlayEdgeSound();
	}

	// Bounce off bottom
	if (y >= WINDOW_HEIGHT)
	{
		velocity.j = -std::abs(velocity.j);
		y = WINDOW_HEIGHT - radius;
		sound.PlayEdgeSound();
	}
	sprite.setPosition(x, y);
}

bool Puck::checkTopGoal()
{
	return y <= radius && x >= leftBound && x <= rightBound;
	sound.PlayGoalSound();
}

bool Puck::checkBottomGoal()
{
	return y >= window->getSize().y && x >= leftBound && x <= rightBound;
	sound.PlayGoalSound();
}

void Puck::reset()
{
	velocity.i = 0;
	velocity.j = 0;

	x = WINDOW_WIDTH / 2;
	y = WINDOW_HEIGHT / 2;
}

bool Puck::checkCollision(Player p)
{
	if (std::pow(x - p.x, 2) + std::pow(y - p.y, 2)
		<= std::pow(p.radius + radius, 2))
	{
		sound.PlayPlayerSound();
		Vector2d collisionDirection(x - p.x, y - p.y);
		velocity = p.velocity.proj(collisionDirection).plus(velocity.proj(collisionDirection).times(-1)
			.plus(velocity.proj(Vector2d(collisionDirection.j, -collisionDirection.i)))).times(0.9);
		return true;
	}
	return false;
}

Puck::~Puck()
{
}
