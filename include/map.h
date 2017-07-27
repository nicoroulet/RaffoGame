#pragma once

#include "drawable.h"
#include "camera.h"

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
    void move();
    int pos_x();
    int pos_y();
    float rotation();
private:
    int x, y;
    float direction;
};

template <class TilePath>
Tile<TilePath>::Tile(int x, int y) : x(x), y(y), direction(0) {}

template <class TilePath>
void Tile<TilePath>::draw() {
    al_draw_bitmap(this->bitmap, x, y, 0);
}

// Testing (movement of ship)
template <class TilePath>
void Tile<TilePath>::move() {
  //x -= 1;
  y += 15; 
  direction += 0.005; 
} 

template <class TilePath>
int Tile<TilePath>::pos_x() {
  return x;
} 

template <class TilePath>
int Tile<TilePath>::pos_y() {
  return y;
}

template <class TilePath>
float Tile<TilePath>::rotation() {
  return direction;
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

