#pragma once

#include <allegro5/allegro.h>
//#include "ship.h"
#include "helpers.h"

class Camera {
public:
    Camera(int width, int height);
    //static Camera &instance();
    //Camera(const Camera &) = delete;
    //Camera &operator=(const Camera &) = delete;

    //bool changed(Ship *ship) const;
    //void set_center(Ship *ship);
    int get_pos_x();
    int get_pos_y();
    void set_zoom(float scale);
    void set_position(int x, int y, float rotate);
    void set_transform_identity();
    void set_transform_translate();
    void set_transform_fixed_ship_ship();
    void set_transform_fixed_ship_map();
    void set_transform_fixed_map_ship();
    void set_transform_fixed_map_map();

private:
    void updatePosition();

    //Ship *center;
    int pos_x;
    int pos_y;
    radians rotation;
    float zoom;
    float previous_zoom;
    int screen_width;
    int screen_height;
    ALLEGRO_TRANSFORM transform;
};

enum CameraShot {
	FIX_SHIP,
	FIX_MAP,
	FREE
};

// class Camera {
// public:
//     Camera();
//     /*
//      * The camera is always centered on a ship (no free mode for now)
//      */
//     void set_center(std::shared_ptr<Ship> ship);
//     void set_camera_map();
//     void set_camera_ship();
//     void set_camera_third_ship(std::shared_ptr<Ship> third_ship);
// private:
//     std::shared_ptr<Ship> center_ship;
//     ALLEGRO_TRANSFORM transform;
// }