#ifndef GROUND_H
#define GROUND_H

#include "Entity.h"

class Ground : public Entity {
public:
	Ground(b2World& world, float X, float Y);
};

#endif // !GROUND_H
