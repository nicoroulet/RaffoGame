#include "ship.h"
#include "weather.h"

#include <math.h>

const char *CaravelPath::path = "res/ships/caravel.png";

Ship::Ship(int x, int y, sp<Drawable> drawable) :
    x(x),
    y(y),
    drawable(drawable),
    rotation(0),
    speed(30),
    height(0),
    width(0),
    sails_aperture(true),
    sails_efficiency(1)
    {}

void Ship::add_crew(sp<Unit> unit) {
    crew.push_back(unit);
}

void Ship::draw(Camera &camera) {
    move();
    camera.set_transform_ship();

    drawable->draw(- drawable->get_width() / 2, - drawable->get_height() / 2);
    for (auto &unit : crew) {
        unit->draw();
    }
}

void Ship::move() {
    /* Difference between Ship speed and Wind speed 
    proportional to the angle of the ship to the wind 
    This calculation could change depending type of sails */
    int w_speed = Weather::wind_speed;
    radians w_direction = Weather::wind_direction;
    float push = (w_speed-speed) * (cos(w_direction-rotation)+1)/2;
    /* Hull drag could be a Ship modifier */
    float drag = 0.05;
    /* Sails could be a Ship Modifier 
    * Change Rate could depend on crew manning sails
    */
    float sails_type = 0.8;
    float sails_change_rate = 0.1;
    /* Sails calculation */
    sails_efficiency += (sails_aperture - sails_efficiency)*sails_change_rate;
    /* New speed with inertia */
    float acceleration = 0.02;
    goal_speed = (1-drag)*sails_type*(speed + push*sails_efficiency);
    speed += (goal_speed-speed)*acceleration;

    x -= speed * sin(rotation);
    y -= speed * cos(rotation);
}

void Ship::turn(float rotate, int direction) {
    /* handling could be a Ship modifier */
    float handling = 0.9;
    rotation += direction*rotate*handling*(0.1*speed);
    /* Rotation penalty could be a Ship Modifier */
    float turn_penalty = 0.99;
    speed *= turn_penalty;
}

void Ship::change_sails_aperture() {
  sails_aperture = !sails_aperture;
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
