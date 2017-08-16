#pragma once

#include "helpers.h"
#include "geometry.h"

class Ship;

class Sail {
public:
    Sail();
    /*
     * Compute push vector, relative to the ship's direction.
     */
    virtual Vector2D calculate_push(const Vector2D &ship_direction) = 0;
    void lower_sail();
    void spread_sail();
protected:
    /*
     * Sail angle relative to the ship.
     */
    radians angle;

    /*
     * Sail efficiency, fraction of wind speed that the sail is able to harness.
     */
    float efficiency;

    /*
     * How spread the sail is. Also idicates the fraction of the wind that is
     * harnessed.
     */
    float spread;

    /*
     * Ship on which the sail is placed.
     */
    // sp<Ship> ship;
};

class SquareSail : public Sail {
public:
    virtual Vector2D calculate_push(const Vector2D &ship_direction) override;
};