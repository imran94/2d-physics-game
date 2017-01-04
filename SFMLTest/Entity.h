#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>

class Entity {
public:
	const float SCALE = 5.f;
	b2Body* Body;
	bool toBeDestroyed;

public:
	~Entity();
};

#endif // !ENTITY_H
