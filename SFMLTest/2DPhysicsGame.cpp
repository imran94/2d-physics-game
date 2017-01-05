// SFMLTest.cpp : Defines the entry point for the console application.
//
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"
#include "Ground.h"
#include "Box.h"
#include "Player.h"
#include <typeinfo>

using namespace std;

const float SCALE = 5.f;
const float DEGTORAD = (b2_pi / 180);

void CreateGround(b2World& world, float X, float Y);
void CreateBox(b2World& world, int MouseX, int MouseY);
void Particles(b2World& world, int MouseX, int MouseY);

std::vector<Entity*> entitiesToBeRemoved;
void* boxTag;

class MyContactListener : public b2ContactListener {
	void BeginContact(b2Contact* contact)
	{	
		Entity *e = new Entity();

		// Get first fixture in contact
		void* userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		if (userDataA == e->boxData)
		{
			entitiesToBeRemoved.push_back(static_cast<Box*>(userDataA));
			
			if (userDataB == e->groundData)
			{
				entitiesToBeRemoved.push_back(static_cast<Ground*>(userDataB));
			}
			else if (userDataB == e->playerData)
			{
				entitiesToBeRemoved.push_back(static_cast<Player*>(userDataB));
			}
		}

		if (userDataA == e->groundData)
		{
			entitiesToBeRemoved.push_back(static_cast<Ground*>(userDataA));

			if (userDataB == e->boxData)
			{
				entitiesToBeRemoved.push_back(static_cast<Box*>(userDataB));
			}
		}

		if (userDataA == e->playerData)
		{
			entitiesToBeRemoved.push_back(static_cast<Player*>(userDataA));
			
			if (userDataB == e->boxData)
			{
				entitiesToBeRemoved.push_back(static_cast<Box*>(userDataB));
			}
		}
	}

	void EndContact(b2Contact* contact)
	{

	}
};

MyContactListener myContactListenerInstance;
void* particleTag;
void* groundTag;

int main()
{
	Entity* e = new Entity();

	//Construct a b2World
	b2Vec2 gravity(0.0f, 30.f);
	b2World world(gravity);

	//Request b2World's body factory to construct a b2Body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Bomb Survival");
	window.setFramerateLimit(60);

	for (int i = 600 / 6; i < 600; i += 600 / 6)
	{
		for (int j = 0; j <= 800; j += 100) 
		{
			CreateGround(world, j * 1.f, i * 1.f);
		}
	}

	//Load Texture
	sf::Texture groundTex;
	sf::Texture boxTex;
	groundTex.loadFromFile("Assets\\Texture\\groundtexture.bmp");
	boxTex.loadFromFile("Assets\\Texture\\boxtexture2.bmp");

	int x = window.getSize().x / 2;
	int y = 15;

	Player* playa = new Player(world, "Assets\\Texture\\Player.png", x, y);

	cout << "Press B for Allahuakbar\n";

	//Disable multiple key presses
	//window.setKeyRepeatEnabled(false);
	
	world.SetContactListener(&myContactListenerInstance);

	bool leftButtonPressed = false;

	while (window.isOpen())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cout << "Left button pressed\n";
			int MouseX = sf::Mouse::getPosition(window).x;
			int MouseY = sf::Mouse::getPosition(window).y;
			CreateBox(world, MouseX, MouseY);
			leftButtonPressed = true;
		}
		else
		{
			leftButtonPressed = false;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					if (event.type == sf::Event::Closed)
						window.close();
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
					{
						int MouseX = sf::Mouse::getPosition(window).x;
						int MouseY = sf::Mouse::getPosition(window).y;
						//Particles(world, MouseX, MouseY);
					}
					break;
			}
		}

		//playa->drawPlayerBox(world);

		//Player Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//playa->playerMovement('u', 6.0);
			
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//playa->playerMovement('d', 6.0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playa->update(MS_LEFT);
			//playa->playerMovement('l', 6.0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playa->update(MS_RIGHT);
			//playa->playerMovement('r', 6.0);
		}
		else 
		{
			playa->update(MS_STOP);
		}

		world.Step(1 / 60.f, 8, 10);
		window.clear();

		//playa.drawPlayerBox(world, window);

		for (int i = 0; i < entitiesToBeRemoved.size(); i++)
		{
			delete entitiesToBeRemoved[i];
		}
		entitiesToBeRemoved.clear();

		//Drawing sprites
		for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				//Render Particles
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

				//Render player
				if (BodyIterator->GetUserData() == playa->playerData)
				{
					sf::Sprite parSprite;
					parSprite.setTexture(boxTex);
					parSprite.setColor(sf::Color::White);
					parSprite.setOrigin(14.5f, 14.5f);
					//Set the position of the sprite to that of the dynamicbody
					parSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					parSprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
					parSprite.setScale(1.f, 1.f);
					window.draw(parSprite);
				}

				//Render boxes
				if (BodyIterator->GetUserData() == e->boxData)
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
					//cout << "Sprite Drawn\n";
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
	Ground* g = new Ground(world, X, Y);
}

void CreateBox(b2World& world, int MouseX, int MouseY)
{
	new Box(world, MouseX, MouseY);
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