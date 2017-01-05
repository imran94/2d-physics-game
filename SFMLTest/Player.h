#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\\Box2D.h>
#include <iostream>
#include "Entity.h"
using namespace std;

class Player : public Entity
{
private:
	sf::Texture plTex;
	sf::Sprite plSprite;

public:
	Player(std::string imgDirectory)
	{
		if (!plTex.loadFromFile(imgDirectory))
		{
			std::cerr << "Error: Player Texture\n";
		}
		plSprite.setTexture(plTex);
	}

	void drawPlayer(sf::RenderWindow &window)
	{
		window.draw(plSprite);
	}

	void drawPlayerBox(b2World& world)
	{
		b2BodyDef bodyDef;
		bodyDef.position = b2Vec2(5, 0);
		bodyDef.type = b2_dynamicBody;
		Body = world.CreateBody(&bodyDef);
		Body->SetUserData(playerData);

		b2PolygonShape shape;
		shape.SetAsBox(2, 2);

		b2FixtureDef fixDef;
		fixDef.density = 1.f;
		fixDef.friction = 1.f;
		fixDef.shape = &shape;
		Body->CreateFixture(&fixDef);
	}

	void playerMovement(char direction, float moveSpeed)
	{
		if (direction == 'u')
			plSprite.move(0, -moveSpeed);
		else if (direction == 'd')
			plSprite.move(0, moveSpeed);
		else if (direction == 'l')
			plSprite.move(-moveSpeed, 0);
		else if (direction == 'r')
			plSprite.move(moveSpeed, 0);
	}
};