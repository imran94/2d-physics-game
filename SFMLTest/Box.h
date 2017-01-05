#ifndef BOX_H
#define BOX_H

#include "Entity.h"

class Box : public Entity {
public:
	void* boxData;

public:
	Box(b2World &world, int x, int y);
};

#endif // !BOX_H
