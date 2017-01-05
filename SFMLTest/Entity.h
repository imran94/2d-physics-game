#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>

struct Data {
	int x;
};

class Entity {
public:
	const float SCALE = 5.f;
	b2Body* Body;
	bool toBeDestroyed;

	void* groundData;
	void* boxData;
	void* playerData;

public:
	~Entity();
};

#endif // !ENTITY_H
