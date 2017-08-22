#pragma once

#include "drawable.h"
#include "camera.h"
#include "sail.h"
#include "unit.h"

// TODO: remove later
// #include "map.h"

class CaravelPath {
public:
    static const char *path;
};

class Ship {
public:
    void add_crew(sp<Unit> unit);
    void draw(Camera &camera);
    void move();
    int pos_x();
    int pos_y();
    float get_rotation();
    void turn_left();
    void turn_right();
    void spread_sails();
    void lower_sails();
protected:
    void turn(float rotate);
    Ship(int x, int y, sp<Drawable> drawable);

    Vector2D calculate_keel_force();

    sp<Drawable> drawable;
    std::vector<sp<Unit>> crew;

    Vector2D position;
    Vector2D direction;
    // radians rotation;
    Vector2D speed;
    int height, width;
    float mass;
    // bool sails_aperture;
    // float sails_efficiency;

    std::vector<sp<Sail>> sails;
};

template <class ShipPath>
class ConcreteShip : public Ship {
public:
    ConcreteShip(int x, int y);
};

// typedef SimpleDrawable<ShipPath>
template <class ShipPath>
ConcreteShip<ShipPath>::ConcreteShip(int x, int y) :
    Ship(x, y, std::make_shared<SimpleDrawable<ShipPath>>())
    {}

class Caravel : public ConcreteShip<CaravelPath> {
public:
    Caravel(int x, int y) :
        ConcreteShip<CaravelPath>(x, y)
        {
            this->sails.push_back(std::make_shared<TriangleSail>());
        }
};
