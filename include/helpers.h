#pragma once

typedef float radians;

struct Point {
    int x;
    int y;

    Point(): x(0),y(0) {}
    Point(int pos_x, int pos_y): x(pos_x), y(pos_y) {}

    Point& operator =(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }

    bool operator ==(const Point& p) const {
        return (x == p.x) && (y == p.y);
    }
};