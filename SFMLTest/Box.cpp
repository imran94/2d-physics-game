#include "Box.h"
#include <iostream>

Box::Box(b2World &world, int x, int y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x / SCALE, y / SCALE); //Spawn Position
	BodyDef.type = b2_dynamicBody; //Dynamic body
	Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape; //shape defintion
	Shape.SetAsBox(3.f, 6.f);
	
	b2FixtureDef FixDef; //fixture definition
	FixDef.density = 1.f;
	FixDef.friction = 0.5f;
	FixDef.shape = &Shape;
	Body->CreateFixture(&FixDef);
	
	Body->SetUserData((void*)BOX_DATA);

	std::cout << "Created box at " << Body << std::endl;
}
