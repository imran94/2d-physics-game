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

std::vector<b2Body*> entitiesToBeRemoved;
void* boxTag;

class MyContactListener : public b2ContactListener {
	void BeginContact(b2Contact* contact)
	{	
		cout << "GroundData: " << GROUND_DATA << endl;
		cout << "boxData: " << BOX_DATA << endl;
		cout << "playerData: " << PLAYER_DATA << endl;

		// Get first fixture in contact
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		int userDataA = (int)bodyA->GetUserData();

		b2Body* bodyB = contact->GetFixtureB()->GetBody();
		int userDataB = (int)bodyB->GetUserData();

		if (userDataA == BOX_DATA)
		{
			entitiesToBeRemoved.push_back(bodyA);

			if (userDataB == GROUND_DATA || userDataB == PLAYER_DATA)
			{
				entitiesToBeRemoved.push_back(bodyB);
			}
		}

		if (userDataA == GROUND_DATA && userDataB == BOX_DATA)
		{
			entitiesToBeRemoved.push_back(bodyA);
			entitiesToBeRemoved.push_back(bodyB);
		}

		if (userDataA == PLAYER_DATA && userDataB == BOX_DATA)
		{
			entitiesToBeRemoved.push_back(bodyA);	
			entitiesToBeRemoved.push_back(bodyB);
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

	for (int i = 600 / 4; i < 600; i += 600 / 4)
	{
		for (int j = 0; j <= 800; j += 50) 
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

	world.SetContactListener(&myContactListenerInstance);

	bool leftButtonPressed = false;

	while (window.isOpen())
	{
		window.clear();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!leftButtonPressed)
			{
				cout << "Left button pressed\n";
				int MouseX = sf::Mouse::getPosition(window).x;
				int MouseY = sf::Mouse::getPosition(window).y;
				CreateBox(world, MouseX, MouseY);
				leftButtonPressed = true;
			}
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
			}
		}


		//Player Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playa->update(MS_LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			playa->update(MS_RIGHT);
		}
		else 
		{
			playa->update(MS_STOP);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			playa->jump();
		}

		world.Step(1 / 60.f, 8, 10);
		//playa.drawPlayerBox(world, window);

		for (int i = 0; i < entitiesToBeRemoved.size(); i++)
		{
			b2Body* b = entitiesToBeRemoved[i];
			int n = (int)b->GetUserData();
			b->SetActive(false);
			if (n == BOX_DATA)
				Particles(world, b->GetPosition().x, b->GetPosition().y);
		}
		//entitiesToBeRemoved.clear();

		//Drawing sprites
		for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator; BodyIterator = BodyIterator->GetNext())
		{
			int n = (int) BodyIterator->GetUserData();
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				//Render Particles
				if (n == PARTICLE_DATA && BodyIterator->IsActive())
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
				if (n == PLAYER_DATA && BodyIterator->IsActive())
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
				if (n == BOX_DATA && BodyIterator->IsActive())
				{
					sf::Sprite parSprite;
					parSprite.setTexture(boxTex);
					parSprite.setColor(sf::Color::Red);
					parSprite.setOrigin(14.5f, 14.5f);
					//Set the position of the sprite to that of the dynamicbody
					parSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					parSprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
					parSprite.setScale(1.5f, 1.5f);
					window.draw(parSprite);
					//cout << "Sprite Drawn\n";
				}

			}
			else if (BodyIterator->GetType() == b2_staticBody && n == GROUND_DATA && BodyIterator->IsActive())
			{
				sf::Sprite groundSprite;
				groundSprite.setTexture(groundTex);
				groundSprite.setOrigin(0.f, 8.f);
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
		body->SetUserData((void*)PARTICLE_DATA);
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