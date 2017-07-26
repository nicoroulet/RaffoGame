#include "helpers.h"
#include "ship.h"
#include "camera.h"

Camera::Camera(int width, int height) {
    rotation = 0.f;
    zoom = 1.f;
    previous_zoom = 1.f;
    pos_x = 0;
    pos_y = 0;
    screen_width = width;
    screen_height = height;
}
/*
bool Camera::changed(Ship *ship) const {
    return true;
    //return (ship->get_position() == position) && (zoom == previous_zoom);
}

void Camera::set_center(Ship *ship) {
    center = ship;
}
*/

void Camera::set_transform_identity() {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_use_transform(&transform);
}

void Camera::set_transform_translate() {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, -pos_x, -pos_y);
    al_use_transform(&transform);
}

void Camera::set_transform_ship() {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, -pos_x, -pos_y);
    al_scale_transform(&transform, zoom, zoom);
    al_use_transform(&transform);
}

void Camera::set_transform_map() {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, -pos_x, -pos_y);
    al_rotate_transform(&transform, rotation);
    al_scale_transform(&transform, zoom, zoom);
    al_use_transform(&transform);
}

void Camera::updatePosition() {
    //pos_x = center->get_pos_x();
    //pos_y = center->get_pos_y();
}

void Camera::set_position(int x, int y) {
    /* center in x,y + size of sprite */
    pos_x = x - screen_width / 2 + 512;
    pos_y = y - screen_height / 2 + 512;
}

void Camera::set_zoom(float scale) {
    zoom = scale;
}

int Camera::get_pos_x() {
    return pos_x;
}
int Camera::get_pos_y() {
    return pos_y;
} 