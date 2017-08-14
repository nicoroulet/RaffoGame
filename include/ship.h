#pragma once

#include "drawable.h"
#include "camera.h"
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
    void turn(float rotate, int direction);
    void change_sails_aperture();
protected:
    Ship(int x, int y, sp<Drawable> drawable);
    sp<Drawable> drawable;
    std::vector<sp<Unit>> crew;

    int x, y;
    float rotation;
    float goal_speed;
    float speed;
    int height, width;
    bool sails_aperture;
    float sails_efficiency;
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

typedef ConcreteShip<CaravelPath> Caravel;
