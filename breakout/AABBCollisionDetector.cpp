#include "AABBCollisionDetector.h"

bool AABBCollisionDetector::checkCollision(PositionedObject2D& o1, PositionedObject2D& o2)
{
    auto a1 = AABBObject::createFromPositionObject2D(o1);
    auto a2 = AABBObject::createFromPositionObject2D(o2);

    // check collision
    if (a1.max_x >= a2.min_x && a1.min_x <= a2.max_x && a1.max_y >= a2.min_y && a1.min_y <= a2.max_y)
    {
        return true;
    }

    return false;
}

AABBCollisionDetector::AABBObject AABBCollisionDetector::AABBObject::createFromPositionObject2D(PositionedObject2D& obj)
{
    AABBObject aabb;

    auto top_left_x = obj.getPosition().x;
    auto top_left_y = obj.getPosition().y;
    auto width = obj.getSize().x;
    auto height = obj.getSize().y;

    aabb.min_x = top_left_x;
    aabb.min_y = top_left_y;
    aabb.max_x = top_left_x + width;
    aabb.max_y = top_left_y + height;

    return aabb;
}
