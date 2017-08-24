#pragma once

#include "drawable.h"
#include "camera.h"
#include "ship.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <vector>

#include <iostream>

class WaterTilePath {
public:
    static const char *path;
};

// This is now an alias for SimpleDrawable.
// Maybe it will have more functionality later.
template <class TilePath>
using Tile = SimpleDrawable<TilePath>;
// class Tile : public SimpleDrawable<TilePath> {};

typedef Tile<WaterTilePath> WaterTile;

class Map {
public:
    Map();
    Map(int height, int width);

    void draw(const Vector2D &camera_pos);
private:
    std::vector<std::vector<std::shared_ptr<Drawable>>> matrix;
    int height;
    int width;
};

