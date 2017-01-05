#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\\Box2D.h>
#include <iostream>
#include "Entity.h"
using namespace std;

enum MoveState {
	MS_STOP,
	MS_LEFT,
	MS_RIGHT
};

class Player : public Entity
{
private:
	sf::Texture plTex;
	sf::Sprite plSprite;

public:
	Player(b2World &world, std::string imgDirectory, int x, int y)
	{
		if (!plTex.loadFromFile(imgDirectory))
		{
			std::cerr << "Error: Player Texture\n";
		}
		plSprite.setTexture(plTex);

		b2BodyDef bodyDef;
		bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
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

	void drawPlayer(sf::RenderWindow &window)
	{
		float x = Body->GetPosition().x;
		float y = Body->GetPosition().y;

		plSprite.setPosition(sf::Vector2f(x / SCALE , y / SCALE));
		window.draw(plSprite);
	}

	void drawPlayerBox(b2World& world)
	{
		/*b2BodyDef bodyDef;
		
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
		Body->CreateFixture(&fixDef);*/
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

	void update(MoveState ms)
	{
		int x = 0;
		b2Vec2 vel = Body->GetLinearVelocity();
		switch (ms)
		{
			case MS_LEFT: x = -50;
				cout << "MOVE LEFT" << endl;
					break;
			case MS_RIGHT: x = 50;
				cout << "MOVE RIGHT" << endl;
				break;
			case MS_STOP: 
				cout << "STOP MOVING" << endl;
				break;
		}
		Body->SetLinearVelocity(b2Vec2(x, vel.y));

	}
};