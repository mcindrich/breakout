#pragma once

#include "ICollisionDetector.h"

class AABBCollisionDetector :
    public ICollisionDetector
{
public:
    virtual bool checkCollision(PositionedObject2D& o1, PositionedObject2D& o2) override;

private:
    struct AABBObject {
        float min_x;
        float max_x;
        float min_y;
        float max_y;

        static AABBObject createFromPositionObject2D(PositionedObject2D& obj);
    };
};

