#pragma once

#include "drawable.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <vector>

#include <iostream>

class WaterTilePath {
public:
    static const char *path;
};

template <class TilePath>
class Tile : public Bitmap<TilePath> {
public:
    Tile(int x, int y);
    virtual void draw();
private:
    int x, y;
};

template <class TilePath>
Tile<TilePath>::Tile(int x, int y) : x(x), y(y) {}

template <class TilePath>
void Tile<TilePath>::draw() {
    al_draw_bitmap(this->bitmap, x, y, 0);
}

typedef Tile<WaterTilePath> WaterTile;

class Map {
public:
    Map(int height, int width);

    void draw();
private:
    std::vector<std::vector<std::shared_ptr<Drawable> > > matrix;
    int height;
    int width;
};

