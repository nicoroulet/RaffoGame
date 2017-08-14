#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "sprite.h"
#include "ship.h"
#include "map.h"
#include "menu.h"
#include "unit.h"
#include "camera.h"
#include "cursor.h"
#include "weather.h"
#include "engine.h"

const int FPS = 20;
// const unsigned int granularity = 50;

// struct status {
//  int act_x, act_y;
//  int dst_x, dst_y;
// } stat;

using namespace std;

void initialize_units() {
    // TODO add a compile time list of initializables to avoid this
    // highly error-prone initialization method
    std::cerr << "initializing units" << std::endl;
    PirateBitmap::initialize();
    GreenPirateBitmap::initialize();

    WaterTile::initialize();
    SimpleDrawable<CaravelPath>::initialize();
}

int main(int argc, char const *argv[])
{
    CHECK(al_init(), "Failed to initialize allegro");
    CHECK(al_init_image_addon(), "Failed to initialize images");
    // if (!al_install_audio()) cerr << "Error instalando audio\n";
    // if (!al_init_acodec_addon()) cerr << "Inicializando codecs\n";
    al_init_font_addon();
    CHECK(al_init_ttf_addon(), "Failed to initialize ttf");
    CHECK(al_init_primitives_addon(), "Failed to initialize primitives");

    CHECK(al_install_mouse(), "Failed to install mouse");
    CHECK(al_install_keyboard(), "Failed to install keyboard");


    al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 1, ALLEGRO_SUGGEST);
    // al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
    // al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    // al_set_new_display_flags(ALLEGRO_OPENGL);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY * display = al_create_display(5000, 5000);
    // al_reset_clipping_rectangle();
    // al_clear_to_color(al_map_rgb(0,80,0));
    //audio
    // ALLEGRO_SAMPLE * audio = al_load_sample("audio.wav");
    // if (!audio) cerr << "Error cargando audio\n";
    // if (!al_reserve_samples(1)) cerr << "Error reservando samples\n";
    // // al_play_sample(audio, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    // cerr << "Reproduciendo\n";

    // menu
    // menu menu("res/menu.png");
    // ALLEGRO_BITMAP * button = al_load_bitmap("res/button.png");
    // if (!button) cerr << "Error cargando button\n";
    // ALLEGRO_COLOR color = al_color_cmyk(100,100,100, 100);
    // menu.set_font("res/font.ttf", 20);
    // menu.add_button(50, 50, button, "holaa", color);
    // menu.display(200, 200);

    // initialization
    initialize_units();

    ALLEGRO_BITMAP * cursor_map = al_load_bitmap("res/cursor.png");
    cursor raton(cursor_map, display);

    Engine engine(FPS, display);
    engine.start();
    engine.loop();
    engine.stop();

    return 0;
}