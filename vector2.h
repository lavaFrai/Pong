#pragma once


class Vector2 {
public:
    float x=0, y=0;

    Vector2() {}
    Vector2(float _x, float _y) { x = _x; y = _y; }

    float length() {
        return sqrt(x * x + y * y);
    }

    void reflectV() {
        y = -y;
    }

    void reflectH() {
        x = -x;
    }
};