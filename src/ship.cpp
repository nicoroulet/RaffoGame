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
#if 0
    /* Difference between Ship speed and Wind speed
    proportional to the angle of the ship to the wind
    This calculation could change depending type of sails */
    int w_speed = Weather::wind_speed;
    radians w_direction = Weather::wind_direction;
    float push = (w_speed - speed) * (cos(w_direction - rotation) + 1) / 2;
    /* Hull drag could be a Ship modifier */
    float drag = 0.05;
    /* Sails could be a Ship Modifier
    * Change Rate could depend on crew manning sails
    */
    float sails_type = 0.8;
    float sails_change_rate = 0.1;
    /* Sails calculation */
    sails_efficiency += (sails_aperture - sails_efficiency) * sails_change_rate;
    /* New speed with inertia */
    float acceleration = 0.02;
    float goal_speed = (1 - drag) * sails_type * (speed + push * sails_efficiency);
    speed += (goal_speed-speed)*acceleration;
#endif
    Vector2D push(0, 0);
    for (auto &sail : sails) {
        push += sail->calculate_push(this->direction);
    }
    Vector2D drag(speed * -0.01);

    // DBG(push);
    // DBG(norm(push));
    // DBG(drag);
    // DBG(norm(drag));
    // DBG(projection(Vector2D(1,0), Vector2D(1,1)));
    speed += push + drag;
    position += speed;
    // x -= speed * sin(rotation);
    // y -= speed * cos(rotation);
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
    direction = rotate(direction, rotation * handling * (0.1 * norm(speed)));
    speed = rotate(speed, rotation * handling * (0.1 * norm(speed)));
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
