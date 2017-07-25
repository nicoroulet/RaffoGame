#pragma once

#include "drawable.h"

// TODO: remove later
#include "map.h"

class CaravelPath {
public:
    static const char *path;
};

typedef Tile<CaravelPath> Ship;

// template <class ShipPath>
// class Ship : public Bitmap<ShipPath> {
// public:
//     Ship(int x, int y);
//     virtual void draw();
// private:
//     int x, y;
// }

