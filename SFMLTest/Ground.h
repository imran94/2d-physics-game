#ifndef GROUND_H
#define GROUND_H

#include "Entity.h"

class Ground : public Entity {
public:
	Ground(b2World& world, float X, float Y, int index);
};

#endif // !GROUND_H
