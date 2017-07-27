#include "ship.h"

#include <math.h>

const char *CaravelPath::path = "res/ships/caravel.png";

Ship::Ship(int x, int y, sp<Drawable> drawable) :
    x(x),
    y(y),
    drawable(drawable),
    rotation(0),
    speed(30),
    height(0),
    width(0)
    {}

void Ship::add_crew(sp<Unit> unit) {
    crew.push_back(unit);
}

void Ship::draw(Camera &camera) {
    // FIXME: set proper cameras
    move();
    camera.set_transform_fixed_ship_ship();

    drawable->draw(- drawable->get_width() / 2, - drawable->get_height() / 2);
    for (auto &unit : crew) {
        unit->draw();
    }
}

void Ship::move() {
    x -= speed * sin(rotation);
    y -= speed * cos(rotation);
}

void Ship::turn_left(float rotate) {
    rotation += rotate*0.1*speed;
}

void Ship::turn_right(float rotate) {
    rotation -= rotate*0.1*speed;
}

int Ship::pos_x() {
    return x;
}

int Ship::pos_y() {
    return y;
}

float Ship::get_rotation() {
    return rotation;
}
