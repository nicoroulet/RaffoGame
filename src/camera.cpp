#include "helpers.h"
#include "ship.h"
#include "camera.h"

Camera::Camera(int width, int height) {
    rotation = 0.f;
    zoom = 1.f;
    pos_x = 0;
    pos_y = 0;
    screen_width = width;
    screen_height = height;
    shot = MAP;
}
/*
void Camera::set_center(Ship *ship) {
    center = ship;
}
*/

const float Camera::ZOOM_LIM_IN = 1.2;

const float Camera::ZOOM_LIM_OUT = 0.3;

void Camera::set_transform_ship() {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_scale_transform(&transform, zoom, zoom);
    if (shot == MAP) {
        al_rotate_transform(&transform, -rotation);
    }
    al_translate_transform(&transform, screen_width * 0.5, screen_height * 0.5);
    al_use_transform(&transform);
}


void Camera::set_transform_map() {
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    al_translate_transform(&transform, -pos_x, -pos_y);
    if (shot == SHIP) {
        al_rotate_transform(&transform, rotation);
    }
    al_scale_transform(&transform, zoom, zoom);
    al_translate_transform(&transform, screen_width * 0.5, screen_height * 0.5);
    al_use_transform(&transform);
}

void Camera::set_position(int x, int y, float rotate) {
    /* center in x,y + size of sprite
     * Hardcorded sprite offset TODO
     */
    rotation = rotate;
    pos_x = x - screen_width / 2 + 1090;
    pos_y = y - screen_height / 2 + 1250;

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

int Camera::get_pos_x() {
    return pos_x;
}
int Camera::get_pos_y() {
    return pos_y;
}