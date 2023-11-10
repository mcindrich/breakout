#pragma once

#include "PositionedObject2D.h"

class ICollisionDetector
{
public:
	// checks if the positioned objects collide
	virtual bool checkCollision(PositionedObject2D& o1, PositionedObject2D& o2) = 0;
};

