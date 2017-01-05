#include "Ground.h"
#include <iostream>

Ground::Ground(b2World& world, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / 3.f, Y / 5.f);
	BodyDef.type = b2_staticBody;
	Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((400.f / 2) / SCALE, (16.f / 2) / SCALE);
	
	b2FixtureDef fixDef;
	fixDef.density = 1.f;
	fixDef.friction = 1.5f;
	fixDef.shape = &Shape;
	Body->CreateFixture(&fixDef);
	Body->SetUserData((void*)GROUND_DATA);

	std::cout << "Created ground at " << Body << std::endl;
}