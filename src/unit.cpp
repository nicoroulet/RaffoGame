#include "unit.h"
#include "fastsqrt.h"

#include <iostream>
#include <math.h>

Unit::Unit(SpriteBase *sprite) :
    selected(false),
    sprite(sprite)
    {}

Direction calculate_direction(float d_x, float d_y) {
    static const Direction direction_lookup_table[9] =
       {RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT};
    // angle from positive x axis in radians.
    // Negative values on 3rd and 4th quadrant
    double angle = atan2(-d_y, d_x);
    return direction_lookup_table[(int) (angle * 4 / M_PI + 4.5)];
}

/*
 * FIXME: decide whether x, y should be relative or absolute
 * Reimplement after relative positions have been added
 */
void Unit::move(int x, int y) {
    dst_x = x - sprite->framesize / 2;
    dst_y = y - sprite->framesize / 2;
    float d_x = dst_x - x;
    float d_y = dst_y - y;
    sprite->change_direction(calculate_direction(d_x, d_y));
    sprite->change_status(WALK);
}

/*
 * Unit is drawn considering (0, 0) is the center of the underlaying ship.
 * An appropriate transform should be used to have a correct drawing.
 */
void Unit::draw() {
    float d_x = dst_x - pos_x;
    float d_y = dst_y - pos_y;

    float dist = fastsqrt(d_x * d_x + d_y * d_y);
    // TODO: clean this code
    pos_x += d_x * ((speed < dist)? speed : dist) / dist;
    pos_y += d_y * ((speed < dist)? speed : dist) / dist;
    if (speed >= dist) {
        sprite->change_status(IDLE);
    }
    sprite->draw(pos_x, pos_y, selected);
}

void Unit::select() {
    selected = true;
}

void Unit::unselect() {
    selected = false;
}

void Unit::set_position(int x, int y) {
    pos_x = x-1;
    pos_y = y-1;
    dst_x = x;
    dst_y = y;
    // draw();
}

int Unit::y() {
    return pos_y;
}

int Unit::x() {
    return pos_x;
}

// bool Unit::operator<(Unit & other) {
//     return y + sprite->framesize < other.y +
//            other.sprite->framesize;
// }

bool Unit::is_clicked(int x, int y) {
    return sprite->is_clicked(x, y);
}

bool Unit::is_broadly_clicked(int x, int y) {
    return sprite->is_broadly_clicked(x, y);
}

bool Unit::intersects(rectangle & rect) {
    rectangle rect2 = sprite->get_rectangle();
    return rect.intersect(rect2).is_valid();
}

float Unit::speed = 30;
