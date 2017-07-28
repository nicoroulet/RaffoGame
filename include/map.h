#pragma once

#include "drawable.h"
#include "camera.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <vector>
#include <math.h>

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
    float get_rotation();
    void turn_left(float rotate);
    void turn_right(float rotate);
private:
    int x, y;
    float rotation;
    float speed;
};

template <class TilePath>
Tile<TilePath>::Tile(int x, int y) : x(x), y(y), rotation(0), speed(50) {}

template <class TilePath>
void Tile<TilePath>::draw() {
    al_draw_bitmap(this->bitmap, x, y, 0);
}

// Testing (movement of ship)
template <class TilePath>
void Tile<TilePath>::move() {
  x -= speed * sin(rotation);
  y -= speed * cos(rotation);
}

template <class TilePath>
void Tile<TilePath>::turn_left(float rotate) {
  rotation += rotate*0.1*speed;
}

template <class TilePath>
void Tile<TilePath>::turn_right(float rotate) {
  rotation -= rotate*0.1*speed;
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
float Tile<TilePath>::get_rotation() {
  return rotation;
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

