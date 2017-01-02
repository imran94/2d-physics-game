// SFMLTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>


int main()
{
	//Construct a b2World
	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	//Request b2World's body factory to construct a b2Body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	sf::RenderWindow window(sf::VideoMode(500, 300), "YPWong is a nigger");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}


    return 0;
}

