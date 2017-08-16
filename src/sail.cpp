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

Vector2D SquareSail::calculate_push(const Vector2D &ship_direction,
                                    const Vector2D &ship_speed) {
    Vector2D sail_direction = rotate(ship_direction, this->angle);
    Vector2D relative_wind = Weather::wind - ship_speed;
    return projection(relative_wind, sail_direction) * this->efficiency
                                                     * this->spread;
}
