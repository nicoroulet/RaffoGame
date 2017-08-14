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
    int fps;
    int window_width;
    int window_height;
    ALLEGRO_DISPLAY *display;

    bool shift;
    bool lctrl;
    bool click;
    bool turning_right;
    bool turning_left;

    ALLEGRO_EVENT_QUEUE *events;
    ALLEGRO_EVENT_SOURCE *mouse;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_SOURCE *keyboard;

    Camera camera;
    CameraShot shot;
};