#ifndef BOX_H
#define BOX_H

#include "Entity.h"

class Box : public Entity {
public:
	Box(b2World &world, int x, int y, int index);
};

#endif // !BOX_H
