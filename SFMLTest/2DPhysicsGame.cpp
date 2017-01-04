// SFMLTest.cpp : Defines the entry point for the console application.
//
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include "Player.h"

using namespace std;

const float SCALE = 5.f;
const float DEGTORAD = (b2_pi / 180);

void CreateGround(b2World& world, float X, float Y);
void CreateBox(b2World& world, int MouseX, int MouseY);
void Particles(b2World& world, int MouseX, int MouseY);
void* particleTag;
void* groundTag;

int main()
{
	//Construct a b2World
	b2Vec2 gravity(0.0f, 9.8f);
	b2World world(gravity);
	CreateGround(world, 400.f, 500.f);

	//Request b2World's body factory to construct a b2Body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "YPWong is a nigger");
	window.setFramerateLimit(60);
	
	//Load Texture
	sf::Texture groundTex;
	sf::Texture boxTex;
	groundTex.loadFromFile("Assets\\Texture\\groundtexture.bmp");
	boxTex.loadFromFile("Assets\\Texture\\boxtexture2.bmp");
	Player playa("Assets\\Texture\\Player.png");

	cout << "Press B for Allahuakbar\n";

	//Disable multiple key presses
	window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		//{
		//	int MouseX = sf::Mouse::getPosition(window).x;
		//	int MouseY = sf::Mouse::getPosition(window).y;
		//	CreateBox(world, MouseX, MouseY);
		//}

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				if (event.type == sf::Event::Closed)
					window.close();
				break;
			}
			case sf::Event::KeyPressed:

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
				{
					int MouseX = sf::Mouse::getPosition(window).x;
					int MouseY = sf::Mouse::getPosition(window).y;
					Particles(world, MouseX, MouseY);
				}
			}
		}

		playa.drawPlayerBox(world);

		//Player Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			playa.playerMovement('u', 6.0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			playa.playerMovement('d', 6.0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playa.playerMovement('l', 6.0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playa.playerMovement('r', 6.0);
		}

		world.Step(1 / 60.f, 8, 10);
		window.clear();

		//playa.drawPlayerBox(world, window);

		//Drawing sprites
		for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator; BodyIterator = BodyIterator->GetNext())
		{
			//if (BodyIterator->GetType() == b2_dynamicBody && BodyIterator->GetUserData() == particleTag)
			//{
			//	sf::Sprite parSprite;
			//	parSprite.setTexture(boxTex);
			//	parSprite.setColor(sf::Color::Red);
			//	parSprite.setOrigin(14.5f, 14.5f);
			//	//Set the position of the sprite to that of the dynamicbody
			//	parSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			//	parSprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			//	parSprite.setScale(0.5f, 0.5f);
			//	window.draw(parSprite);
			//	//cout << "Sprite Drawn\n";
			//}
			//else if (BodyIterator->GetType() == b2_staticBody && BodyIterator->GetUserData() == groundTag)
			//{
			//	sf::Sprite groundSprite;
			//	groundSprite.setTexture(groundTex);
			//	groundSprite.setOrigin(350.f, 8.f);
			//	groundSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
			//	groundSprite.setRotation(180 / b2_pi*BodyIterator->GetAngle());
			//	window.draw(groundSprite);
			//}
			//else if (BodyIterator->GetUserData() == playa.playerData &&BodyIterator->GetType() == b2_dynamicBody )
			//{
			//	cout << "Player drawn\n";
			//	playa.drawPlayer(window);
			//}


			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				if (BodyIterator->GetUserData() == particleTag)
				{
					sf::Sprite parSprite;
					parSprite.setTexture(boxTex);
					parSprite.setColor(sf::Color::Red);
					parSprite.setOrigin(14.5f, 14.5f);
					//Set the position of the sprite to that of the dynamicbody
					parSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					parSprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
					parSprite.setScale(0.5f, 0.5f);
					window.draw(parSprite);
				}
				if (BodyIterator->GetUserData() == playa.playerData)
				{
					cout << "Player drawn\n";
					playa.drawPlayer(window);
				}
			}
			else if (BodyIterator->GetType() == b2_staticBody && BodyIterator->GetUserData() == groundTag)
			{
				sf::Sprite groundSprite;
				groundSprite.setTexture(groundTex);
				groundSprite.setOrigin(350.f, 8.f);
				groundSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				groundSprite.setRotation(180 / b2_pi*BodyIterator->GetAngle());
				window.draw(groundSprite);
			}

		}

		window.display();
	}
    return 0;
}

void CreateGround(b2World& world, float X, float Y)
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(X / 3.f, Y / 5.f);
	bodyDef.type = b2_staticBody;
	b2Body* body = world.CreateBody(&bodyDef);
	body->SetUserData(groundTag);

	b2PolygonShape shape;
	shape.SetAsBox((700.f / 2) / SCALE, (16.f / 2) / SCALE);
	b2FixtureDef fixDef;
	fixDef.density = 0.f;
	fixDef.shape = &shape;
	body->CreateFixture(&fixDef);
}

void CreateBox(b2World& world, int MouseX, int MouseY)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE); //Spawn Position
	BodyDef.type = b2_dynamicBody; //Dynamic body
	b2Body* Body = world.CreateBody(&BodyDef);

	b2PolygonShape shape; //shape defintion
	shape.SetAsBox(3.f, 3.f);
	b2FixtureDef FixDef; //fixture definition
	FixDef.density = 1.f;
	FixDef.friction = 0.5f;
	FixDef.shape = &shape;
	Body->CreateFixture(&FixDef);
	cout << "CreateBox Completed\n";
}

void Particles(b2World& world, int MouseX, int MouseY)
{
	int numRays = 18;
	float blastPower = 200.f;
	for (int i = 0; i < numRays; i++)
	{
		float ii = i; //somehow the formula only works like this
		float angle = (ii / numRays) * 360; //getting the angle for each particle
		b2Vec2 rayDir(sinf(angle), cosf(angle)); //getting the X and Y coordinates

		cout << i << " " << ii << " "<< angle << endl;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = false;
		bodyDef.bullet = true;
		bodyDef.linearDamping = 0.8f;
		bodyDef.angularDamping = 0.8f;
		bodyDef.gravityScale = 0;
		bodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
		bodyDef.linearVelocity = blastPower * rayDir;
		b2Body* body = world.CreateBody(&bodyDef);
		body->SetUserData(particleTag);
		//b2CircleShape circleShape; //shape definition
		//circleShape.m_radius = 0.05f; //circle radius

		b2PolygonShape Shape; //shape defintion
		Shape.SetAsBox(0.5f, 0.5f);

		b2FixtureDef fixDef;
		fixDef.shape = &Shape;
		fixDef.density = 30.f / numRays;
		fixDef.friction = 0.f;
		fixDef.restitution = 0.99f; //Affects the reflection off of surfaces
		fixDef.filter.groupIndex = 0; //Particle collision Pos values for collision, Neg values for no collision
		body->CreateFixture(&fixDef);
		}
}