#include "Entity.h"

Entity::~Entity()
{
	Body->GetWorld()->DestroyBody(Body);
}