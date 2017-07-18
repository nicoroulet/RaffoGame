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
    Unit(SpriteBase *sprite);

    static float speed;
    SpriteBase *sprite;
    int pos_x;
    int pos_y;
    int dst_x;
    int dst_y;
    bool selected;
};

// TODO: consider renaming
template <class SpriteType>
class ConcreteUnit : public Unit {
public:
    ConcreteUnit();
};

template <class SpriteType>
ConcreteUnit<SpriteType>::ConcreteUnit() :
    Unit(new SpriteType()) // TODO delete in destructor
    {}

// Declare unit types here
typedef ConcreteUnit<PirateSprite> Pirate;
typedef ConcreteUnit<SoldierSprite> Soldier;
