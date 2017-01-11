#include "AIPlayer.h"
#include <cmath>

AIPlayer::AIPlayer(sf::RenderWindow &w) : Player(w)
{
	x = window->getSize().x / 2;
	y = offset;
}

void AIPlayer::move(Puck puck)
{
	double oldX = x;
	double oldY = y;

	if (puck.y < window->getSize().y / 2)
	{
		std::cout << "Puck in range\n";

		velocity.i = puck.x;
		velocity.j = puck.y;
		velocity = velocity.getUnitVector().times(15);

		//velocity = Vector2d(puck.x, puck.y).getUnitVector();
		if (puck.x > x) { x += velocity.i; }
		else { x -= velocity.i; }

		if (puck.y > y) { y += velocity.j; }
		else { y -= velocity.j; }
	}
	else
	{
		std::cout << "Puck out of range\n";

		double destX = window->getSize().x / 2;
		double destY = offset;

		velocity.i = destX;
		velocity.j = destY;
		velocity = velocity.getUnitVector();

		x += velocity.i;
		y += velocity.j;

		if (destX > x) { x += velocity.i; }
		else { x -= velocity.i; }

		if (destY > y) { y += velocity.j; }
		else { y -= velocity.j; }
	}

	// Collide with left wall
	if (x < radius)
	{
		x = radius;
		velocity.i = 0;
	}
	
	// Collide with right wall
	if (x >= window->getSize().x - radius)
	{
		x = window->getSize().x - radius;
		velocity.i = 0;
	}

	// Collide with bottom bounds
	if (y >= window->getSize().y / 2 - radius)
	{
		y = window->getSize().y / 2 - radius;
		velocity.j = 0;
	}

	// Collide with top
	if (y < radius)
	{
		y = radius;
		velocity.j = 0;
	}
}

AIPlayer::~AIPlayer()
{
}
