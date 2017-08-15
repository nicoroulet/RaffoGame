#pragma once

#include "camera.h"
#include "map.h"
#include "ship.h"
#include "unit.h"

#include <allegro5/allegro.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class Engine {
public:
    Engine(int fps, ALLEGRO_DISPLAY *display);
    void start();
    void loop();
    void stop();
private:
    void initialize_map();
    void manage_input(ALLEGRO_EVENT &ev);
    void manage_timer();
    void add_ship(sp<Ship> ship);

    int fps;
    int window_width;
    int window_height;
    ALLEGRO_DISPLAY *display;

    bool shift;
    bool lctrl;
    bool click;
    bool turning_right;
    bool turning_left;
    bool looping;

    ALLEGRO_EVENT last_ev;
    ALLEGRO_EVENT_QUEUE *events;
    ALLEGRO_EVENT_SOURCE *mouse;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_SOURCE *keyboard;

    Map map;
    std::vector<sp<Ship>> ships;
    sp<Ship> main_ship;

    Camera camera;
    CameraShot shot;
};