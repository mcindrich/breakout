#include "AABBCollisionDetector.h"

#include <iostream>

bool AABBCollisionDetector::checkCollision(PositionedObject2D& A, PositionedObject2D& B)
{
    auto a_left_b = A.getRightX() < B.getLeftX();
    auto a_right_b = A.getLeftX() > B.getRightX();
    auto a_below_b = A.getTopY() > B.getBottomY();
    auto a_above_b = A.getBottomY() < B.getTopY();

    // check collision
    if (!(a_left_b || a_right_b || a_below_b || a_above_b))
    {
        return true;
    }

    return false;
}

AABBCollisionDetector::AABBObject AABBCollisionDetector::AABBObject::createFromPositionObject2D(PositionedObject2D& obj)
{
    AABBObject aabb;

    auto top_left_x = obj.getTopLeftPosition().x;
    auto top_left_y = obj.getTopLeftPosition().y;
    auto width = obj.getSize().x;
    auto height = obj.getSize().y;

    aabb.min_x = top_left_x;
    aabb.min_y = top_left_y;
    aabb.max_x = top_left_x + width;
    aabb.max_y = top_left_y + height;

    return aabb;
}
