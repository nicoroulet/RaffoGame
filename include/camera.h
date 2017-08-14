#pragma once

#include <allegro5/allegro.h>
//#include "ship.h"
#include "helpers.h"

enum CameraShot {
	SHIP,
	MAP
};

class Camera {
public:
    Camera(int width, int height);
    //static Camera &instance();
    //Camera(const Camera &) = delete;
    //Camera &operator=(const Camera &) = delete;

    //void set_center(Ship *ship);
    int get_pos_x();
    int get_pos_y();
    void set_zoom(float scale);
    void set_position(int x, int y, float rotate);
    void set_transform_ship();
    void set_transform_map();
    void change_shot();

private:
    //Ship *center;
    int pos_x;
    int pos_y;
    radians rotation;
    float zoom;
    int screen_width;
    int screen_height;
    CameraShot shot;
    ALLEGRO_TRANSFORM transform;
};


// class Camera {
// public:
//     Camera();
//     void set_center(std::shared_ptr<Ship> ship);
//     void set_camera_map();
//     void set_camera_ship();
//     void set_camera_third_ship(std::shared_ptr<Ship> third_ship);
// private:
//     std::shared_ptr<Ship> center_ship;
//     ALLEGRO_TRANSFORM transform;
// }