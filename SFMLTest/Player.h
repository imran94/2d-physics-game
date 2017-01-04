#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\\Box2D.h>
#include <iostream>
using namespace std;

class Player 
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

	void* playerData;
	void drawPlayerBox(b2World& world)
	{
		b2BodyDef bodyDef;
		bodyDef.position = b2Vec2(5, 0);
		bodyDef.type = b2_dynamicBody;
		b2Body* body = world.CreateBody(&bodyDef);
		body->SetUserData(playerData);

		b2PolygonShape shape;
		shape.SetAsBox(2, 2);

		b2FixtureDef fixDef;
		fixDef.density = 1.f;
		fixDef.friction = 1.f;
		fixDef.shape = &shape;
		body->CreateFixture(&fixDef);
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