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
                                    const Vector2D &relative_wind) {
    Vector2D sail_direction = rotate(ship_direction, this->angle);
    return projection(relative_wind, sail_direction) * this->efficiency
                                                     * this->spread;
}

Vector2D TriangleSail::calculate_push(const Vector2D &ship_direction,
                                    const Vector2D &relative_wind) {
    Vector2D deviated_wind = ship_direction *
                             (norm(relative_wind) / norm(ship_direction));
    return (relative_wind - deviated_wind) * this->efficiency * this->spread;
}
