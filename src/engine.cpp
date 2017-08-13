#include "engine.h"

Engine::Engine(int fps, ALLEGRO_DISPLAY *display) :
    fps{fps},
    window_width{al_get_display_width(display)},
    window_height{al_get_display_height(display)},
    display{display},
    shift{false},
    lctrl{false},
    click{false},
    turning_right{false},
    turning_left{false},
    camera(window_width, window_height),
    shot{SHIP}
    {}

const float Engine::ZOOM_LIM_IN = 1.2;
const float Engine::ZOOM_LIM_OUT = 0.3;

void Engine::start() {
    events = al_create_event_queue();
    if (!events) std::cerr << "Engine ERROR: creating event queue\n";
    mouse = al_get_mouse_event_source();
    if (!mouse) std::cerr << "Engine ERROR: creating mouse source, did not "
                             "install mouse subsystem";
    al_register_event_source(events, mouse);

    timer = al_create_timer(1.f/fps);
    if (!timer) std::cerr << "Error creando timer\n";
    al_register_event_source(events, al_get_display_event_source(display));
    al_register_event_source(events, al_get_timer_event_source(timer));
    al_start_timer(timer);

    keyboard = al_get_keyboard_event_source();
    if (!keyboard) std::cerr << "Engine ERROR: creating keyboard source, did "
                                "not install keyboard subsystem";
    al_register_event_source(events, keyboard);

}

void Engine::loop() {

    // FIXME: this should be elsewhere
    Map map(15, 15);
    sp<Ship> ship = std::make_shared<Caravel>(200, 200);
    map.add_ship(ship);
    sp<Unit> pirate1 = std::make_shared<Pirate>();
    pirate1->set_position(50, 50);
    ship->add_crew(pirate1);
    sp<Unit> pirate2 = std::make_shared<Pirate>();
    pirate2->set_position(100, 100);
    ship->add_crew(pirate2);

    int SHOT_VAR = 0;
    float zoom = 1.0, rotate = 0;
    while(true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(events, &ev);
        // if (!ev) cerr << "Error en el mouse event\n";
        switch(ev.type) {
            case ALLEGRO_EVENT_TIMER:
                if (turning_right)
                    ship->turn_right();
                if (turning_left)
                    ship->turn_left();
                    // uMgr.turn_ship_left();
                // uMgr.tick(camera, shot);
                // TODO: consider making camera a singleton instead of passing
                map.draw(camera);
                al_flip_display();
                break;
            // case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            //     // std::cerr << ev.mouse.button;
            //     if (ev.mouse.button == 1) {
            //         uMgr.left_unclick(ev.mouse.x, ev.mouse.y, shift);

            //     }
            //     if (ev.mouse.button == 2) {
            //         uMgr.right_unclick(ev.mouse.x, ev.mouse.y, shift);
            //     }
            //     break;
            // case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            //     if (ev.mouse.button == 1) {
            //         uMgr.left_click(ev.mouse.x, ev.mouse.y);
            //     }
            //     break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                // uMgr.mouse_move(ev.mouse.x, ev.mouse.y);
                if (!lctrl){
                    zoom += ev.mouse.dz * 0.1 * zoom;
                    /* Zoom limits */
                    if (zoom < ZOOM_LIM_OUT) zoom = ZOOM_LIM_OUT;
                    if (zoom > ZOOM_LIM_IN) zoom = ZOOM_LIM_IN;
                    camera.set_zoom(zoom);
                }
                if (lctrl){
                    rotate += ev.mouse.dz * 0.1;
                }
                /* Zoom limits */
                if (zoom < 0.1) zoom = 0.1;
                if (zoom > 10) zoom = 10;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(ev.keyboard.keycode) {
                    /* Check if Keyboard Modifier Flags is better */
                    case ALLEGRO_KEY_ESCAPE:
                        return;
                    case ALLEGRO_KEY_LCTRL:
                        lctrl = true;
                        break;
                    case ALLEGRO_KEY_LSHIFT: case ALLEGRO_KEY_RSHIFT:
                        shift = true;
                        break;
                    case ALLEGRO_KEY_D:
                        turning_right = true;
                        break;
                    case ALLEGRO_KEY_C:
                        ship->change_sails_aperture();
                    case ALLEGRO_KEY_A:
                        turning_left = true;
                        break;
                    case ALLEGRO_KEY_V:
                        camera.change_shot();
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch(ev.keyboard.keycode) {
                    case ALLEGRO_KEY_LCTRL:
                        lctrl = false;
                        break;
                    case ALLEGRO_KEY_LSHIFT: case ALLEGRO_KEY_RSHIFT:
                        shift = false;
                        break;
                    case ALLEGRO_KEY_A:
                        turning_left = false;
                        break;
                    case ALLEGRO_KEY_D:
                        turning_right = false;
                        break;
                }
                break;
            // case ALLEGRO_EVENT_MOUSE_AXES:
            //     al_clear_to_color(al_map_rgb(0,0,0));
            //     al_draw_bitmap(img, ev.mouse.x, ev.mouse.y, 0);
            //     al_flip_display();
            //     break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                return;
        }
    }
}

void Engine::stop() {
    al_destroy_event_queue(events);
    al_destroy_display(display);
}