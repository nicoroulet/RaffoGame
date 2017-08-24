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
    looping{true},
    camera(window_width, window_height),
    shot{SHIP},
    hud(window_width, window_height, camera)
    {}


void Engine::start() {
    events = al_create_event_queue();
    // if (!events) std::cerr << "Engine ERROR: creating event queue\n";
    CHECK(events, "Failed to create event queue");
    mouse = al_get_mouse_event_source();
    CHECK(mouse, "Failed to create mouse source, "
                 "mouse subsystem not installed");
    al_register_event_source(events, mouse);

    timer = al_create_timer(1.f/fps);
    CHECK(timer, "Failed to create timer");
    al_register_event_source(events, al_get_display_event_source(display));
    al_register_event_source(events, al_get_timer_event_source(timer));
    al_start_timer(timer);

    keyboard = al_get_keyboard_event_source();
    CHECK(keyboard, "Failed to create keyboard source, "
                    "keyboard subsystem not installed");
    al_register_event_source(events, keyboard);

}

void Engine::initialize_map() {
    this->map = Map(18, 18);
    this->main_ship = std::make_shared<Caravel>(200, 200);
    sp<Ship> other_ship = std::make_shared<Caravel>(210, 200);
    add_ship(other_ship);
    sp<Unit> pirate1 = std::make_shared<Pirate>();
    pirate1->set_position(25, 25);
    this->main_ship->add_crew(pirate1);
    sp<Unit> pirate2 = std::make_shared<Pirate>();
    pirate2->set_position(-50, -50);
    this->main_ship->add_crew(pirate2);
    sp<Unit> pirate3 = std::make_shared<GreenPirate>();
    pirate3->set_position(-50, -50);
    other_ship->add_crew(pirate3);
}

void Engine::manage_input(ALLEGRO_EVENT &ev) {
    switch(ev.type) {
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
            this->camera.change_zoom(ev.mouse.dz);
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch(ev.keyboard.keycode) {
                /* Check if Keyboard Modifier Flags is better */
                case ALLEGRO_KEY_ESCAPE:
                    this->looping = false;
                case ALLEGRO_KEY_LCTRL:
                    lctrl = true;
                    break;
                case ALLEGRO_KEY_LSHIFT: case ALLEGRO_KEY_RSHIFT:
                    shift = true;
                    break;
                case ALLEGRO_KEY_D:
                    turning_right = true;
                    break;
                case ALLEGRO_KEY_W:
                    this->main_ship->spread_sails();
                    break;
                case ALLEGRO_KEY_S:
                    this->main_ship->lower_sails();
                    break;
                case ALLEGRO_KEY_A:
                    turning_left = true;
                    break;
                case ALLEGRO_KEY_V:
                    this->camera.change_shot();
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
    // if (!ev) cerr << "Error en el mouse event\n";

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            this->looping = false;
    }
}

void Engine::manage_timer() {
    if (turning_right)
        this->main_ship->turn_right();
    if (turning_left)
        this->main_ship->turn_left();
    // TODO: consider making camera a singleton instead of passing

    /* DRAWING */
    this->camera.set_position(this->main_ship->pos(),
                              this->main_ship->get_rotation());
    camera.set_transform_map();
    this->map.draw(this->camera.get_pos());
    main_ship->move();
    camera.set_transform_ship();
    main_ship->draw();
    for (auto &ship : this->ships) {
        ship->move();
        camera.set_transform_other_ship(ship->pos(), ship->get_rotation());
        ship->draw();
    }
    camera.set_transform_identity();
    hud.draw();
    al_flip_display();
}

void Engine::loop() {
    ALLEGRO_EVENT ev;
    initialize_map();
    while(this->looping) {
        al_wait_for_event(events, &ev);
        if (ev.type == ALLEGRO_EVENT_TIMER)
            manage_timer();
        else
            manage_input(ev);
    }
}

void Engine::stop() {
    al_destroy_event_queue(events);
    al_destroy_display(display);
}

void Engine::add_ship(sp<Ship> ship) {
    ships.push_back(ship);
}
