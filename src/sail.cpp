#include "sail.h"
#include "ship.h"
#include "weather.h"
// TODO: unify rotation, orientation and direction names

Sail::Sail() :
    angle(0),
    spread(1),
    efficiency(1)
    {}

void Sail::lower_sail() {
    if (spread > 0) spread -= 0.5;
}

void Sail::spread_sail() {
    if (spread < 1) spread += 0.5;
}

Vector2D SquareSail::calculate_push(radians ship_direction) {
    radians sail_direction = this->angle + ship_direction;
    radians wind_angle = Weather::wind_direction - sail_direction;
    float strength = cos(wind_angle) * this->efficiency * this->spread;
    return unit_vector(this->angle) * strength;
}
