#pragma once
#include "vector2.h"

class Position2 {
public:
    float x=0, y=0;

    Position2() {}
    Position2(float _x, float _y) { x = _x; y = _y; }

    float move(const Vector2& speed) {
        x += speed.x;
        y += speed.y;
    }
};