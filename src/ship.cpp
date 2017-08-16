#include "ship.h"
#include "weather.h"

#include <math.h>

const char *CaravelPath::path = "res/ships/caravel.png";

Ship::Ship(int x, int y, sp<Drawable> drawable) :
    position(x, y),
    drawable(drawable),
    direction(unit_vector(3.14)),
    speed(0, 30),
    height(0),
    width(0)
    // sails_aperture(true),
    // sails_efficiency(1)
    {}

void Ship::add_crew(sp<Unit> unit) {
    crew.push_back(unit);
}

void Ship::draw(Camera &camera) {
    move();
    camera.set_transform_ship();

    drawable->draw(-drawable->get_width() / 2, -drawable->get_height() / 2);
    for (auto &unit : crew) {
        unit->draw();
    }
}

void Ship::move() {
    // TODO: missing sails change rate
    Vector2D push(0, 0);
    for (auto &sail : sails) {
        push += sail->calculate_push(this->direction);
    }
    Vector2D drag(speed * -0.01);

    speed += push + drag + calculate_keel_force();
    position += speed;
}

void Ship::turn_left() {
    turn(-0.01);
}

void Ship::turn_right() {
    turn(0.01);
}

void Ship::turn(float rotation) {
    /* handling could be a Ship modifier */
    float handling = 0.9;
    direction = rotate(this->direction,
                       rotation * handling * (0.1 * norm(this->speed)));
    /* Rotation penalty could be a Ship Modifier */
    float turn_penalty = 0.99;
    speed *= turn_penalty;
}

void Ship::spread_sails() {
    for (auto &sail : sails) {
        sail->spread_sail();
    }
}

void Ship::lower_sails() {
    for (auto &sail : sails) {
        sail->lower_sail();
    }
}

int Ship::pos_x() {
    return position.x;
}

int Ship::pos_y() {
    return position.y;
}

float Ship::get_rotation() {
    return atan2(direction.x, direction.y);
}

Vector2D Ship::calculate_keel_force() {
    return projection(this->speed, this->direction) - this->speed;
}