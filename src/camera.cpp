#include "helpers.h"
#include "ship.h"
#include "camera.h"

Camera::Camera(int width, int height) :
    rotation(0.f),
    zoom(1.f),
    pos(0, 0),
    screen_width(width),
    screen_height(height),
    shot(MAP)
    {}
/*
void Camera::set_center(Ship *ship) {
    center = ship;
}
*/

const float Camera::ZOOM_LIM_IN = 1.2;

const float Camera::ZOOM_LIM_OUT = 0.2;

void Camera::set_transform_ship() {
    al_identity_transform(&transform);
    al_scale_transform(&transform, this->zoom, this->zoom);
    if (shot == MAP) {
        al_rotate_transform(&transform, -rotation);
    }
    al_translate_transform(&transform, screen_width / 2, screen_height / 2);
    al_use_transform(&transform);
}

void Camera::set_transform_other_ship(const Vector2D &ship_pos,
                                      radians ship_rotation) {
    Vector2D translate = ship_pos - this->pos;
    radians rotation = ship_rotation;
    if (shot == SHIP) {
        translate = rotate(translate, this->rotation);
        rotation += this->rotation;
    }
    al_identity_transform(&transform);
    al_rotate_transform(&transform, rotation);
    al_translate_transform(&transform, translate.x, translate.y);
    al_scale_transform(&transform, this->zoom, this->zoom);
    al_translate_transform(&transform, screen_width / 2,
                                       screen_height / 2);
    al_use_transform(&transform);
}

void Camera::set_transform_map() {
    al_identity_transform(&transform);
    al_translate_transform(&transform, -pos.x, -pos.y);
    al_scale_transform(&transform, this->zoom, this->zoom);
    if (shot == SHIP) {
        al_rotate_transform(&transform, rotation);
    }
    al_translate_transform(&transform, screen_width / 2, screen_height / 2);
    al_use_transform(&transform);
}

void Camera::set_transform_identity() {
    al_identity_transform(&transform);
    al_use_transform(&transform);
}

void Camera::set_position(const Vector2D &new_pos, radians new_rotation) {
    this->pos = new_pos - Vector2D(screen_width / 2,
                                   screen_height / 2);
    this->rotation = new_rotation;
}

void Camera::change_shot() {
    shot = CameraShot((shot + 1) % 2);
}

void Camera::change_zoom(float factor) {
    zoom += factor * 0.1 * zoom;
    /* Zoom limits */
    if (zoom < ZOOM_LIM_OUT) zoom = ZOOM_LIM_OUT;
    if (zoom > ZOOM_LIM_IN) zoom = ZOOM_LIM_IN;
}

const Vector2D &Camera::get_pos() const {
    return pos;
}

radians Camera::get_rotation() const {
    if (shot == MAP) {
        return 0;
    }
    return rotation;
}