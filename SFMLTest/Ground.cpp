#include "Ground.h"

Ground::Ground(b2World& world, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / 3.f, Y / 5.f);
	BodyDef.type = b2_staticBody;
	Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((100.f / 2) / SCALE, (16.f / 2) / SCALE);
	b2FixtureDef fixDef;
	fixDef.density = 0.f;
	fixDef.shape = &Shape;
	Body->CreateFixture(&fixDef);
	Body->SetUserData(groundData);

	toBeDestroyed = false;
}