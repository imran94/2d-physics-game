// SFMLTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;

const float SCALE = 5.f;

void CreateBox(b2World& world, int MouseX, int MouseY);

int main()
{

	//Construct a b2World
	b2Vec2 gravity(0.0f, 9.8f);
	b2World world(gravity);

	//Request b2World's body factory to construct a b2Body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "YPWong is a nigger");
	window.setFramerateLimit(60);
	
	//Load Texture
	sf::Texture boxTex;
	boxTex.loadFromFile("Assets\\Texture\\boxtexture2.bmp");

	/*sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);*/


	while (window.isOpen())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int MouseX = sf::Mouse::getPosition(window).x;
			int MouseY = sf::Mouse::getPosition(window).y;
			CreateBox(world, MouseX, MouseY);
			cout << "CreateBox Called\n";
			//system("pause");
		}

		world.Step(1 / 60.f, 8, 9);

		window.clear();

		int BodyCount = 0;

		for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				sf::Sprite sprite;
				sprite.setTexture(boxTex);
				sprite.setOrigin(16.f, 16.f);
				sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				window.draw(sprite);
				cout << "Sprite Drawn\n";
				++BodyCount;
				//break;
			}
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//window.draw(shape);
		//window.clear();
		window.display();
	}
    return 0;
}

void CreateBox(b2World& world, int MouseX, int MouseY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE); //Spawn Position
	BodyDef.type = b2_dynamicBody; //Dynamic body
	b2Body* Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape; //shape defintion
	Shape.SetAsBox(3.f, 3.f);
	b2FixtureDef FixDef; //fixture definition
	FixDef.density = 1.f;
	FixDef.friction = 0.5f;
	FixDef.shape = &Shape;
	Body->CreateFixture(&FixDef);
	cout << "CreateBox Completed\n";
}
