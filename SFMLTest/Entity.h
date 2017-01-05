#ifndef ENTITY_H
#define ENTITY_H

#include <Box2D/Box2D.h>

enum Data {
	GROUND_DATA,
	BOX_DATA,
	PLAYER_DATA
};

class Entity {
public:
	const float SCALE = 5.f;
	b2Body* Body;
	bool toBeDestroyed;	
	Data data;

public:
	~Entity();
};

#endif // !ENTITY_H
