#pragma once
#include "sprite.h"
#include "geometry.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define MAX_NAME_LENGTH 16

class Unit {
public:
    Unit(Unit &u) = delete;

    void move(int x, int y);
    void clear();
    void draw();
    void select();
    void unselect();
    void set_position(int x, int y);
    int y();
    int x();
    bool operator<(Unit & other);
    bool is_clicked(int x, int y);          // check whether the unit sprite is non-transparent in pos x, y
    bool is_broadly_clicked(int x, int y);  // check whether the unit sprite is in pos x, y
    bool intersects(rectangle & rect);

protected:
    // Construct a Unit, getting the sprite
    Unit(Sprite *sprite);

    virtual ALLEGRO_BITMAP *unit_type_bitmap() = 0;
    static float speed;
    Sprite *sprite;
    int pos_x;
    int pos_y;
    int dst_x;
    int dst_y;
    bool selected;
};

class Pirate : public Unit {
public:
    Pirate();
    // sets static values
    // TODO: add uninitialize to destroy the bitmaps
    static void initialize();
protected:
    // stores the bitmap for the class' graphics
    static ALLEGRO_BITMAP *unit_type_bitmap_ptr;
    // retrieve the bitmap
    virtual ALLEGRO_BITMAP *unit_type_bitmap();
};