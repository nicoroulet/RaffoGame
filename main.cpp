#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>
#include "sprite.h"
#include "menu.h"
#include "unit.h"

const int FPS = 10;
// const unsigned int granularity = 50;

// struct status {
// 	int act_x, act_y;
// 	int dst_x, dst_y;
// } stat;

using namespace std;
int main(int argc, char const *argv[])
{
	if (!al_init()) cerr << "Error inicializando allegro\n";
	if (!al_init_image_addon()) cerr << "Error inicializando imagenes\n";
	// if (!al_install_audio()) cerr << "Error instalando audio\n";
	// if (!al_init_acodec_addon()) cerr << "Inicializando codecs\n";
	al_init_font_addon();
	if (!al_init_ttf_addon()) cerr << "Error inicializando ttf\n";


	al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 1, ALLEGRO_SUGGEST);
	// al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
	// al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	// al_set_new_display_flags(ALLEGRO_OPENGL);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_DISPLAY * display = al_create_display(5000, 5000);
	ALLEGRO_BITMAP * backbuffer = al_get_backbuffer(display);
	al_clear_to_color(al_map_rgb(0,0,0));
	//audio
	// ALLEGRO_SAMPLE * audio = al_load_sample("audio.wav");
	// if (!audio) cerr << "Error cargando audio\n";
	// if (!al_reserve_samples(1)) cerr << "Error reservando samples\n";
	// // al_play_sample(audio, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	// cerr << "Reproduciendo\n";
	
	// menu
	// menu menu("resources/menu.png");
	// ALLEGRO_BITMAP * button = al_load_bitmap("resources/button.png");
	// if (!button) cerr << "Error cargando button\n";
	// ALLEGRO_COLOR color = al_color_cmyk(100,100,100, 100);
	// menu.set_font("resources/font.ttf", 20);
	// menu.add_button(50, 50, button, "holaa", color);
	// menu.display(200, 200);
	
	//imagenes
	// vector<ALLEGRO_BITMAP*> bmp(2);
	// bmp[0] = al_load_bitmap("resources/sprite.png");
	// bmp[1] = al_load_bitmap("resources/sprite2.png");
	// // al_draw_bitmap(bmp[0], 0, 0, 0);
	// if (!bmp[0] || !bmp[1]) cerr << "Error loading bitmap\n";
	
	// sprite s(bmp, backbuffer, 50, 50, 50);
	// sprite s2(bmp, backbuffer, 50, 50, 50);
	
	// unit
	cerr << "creando unidad \n";
	ALLEGRO_BITMAP * bmp = al_load_bitmap("resources/Man50.png");
	if (!bmp) cerr << "ERROR: creando bitmap man50\n";
	unit man(bmp, backbuffer, 50);
	cerr << "unidad creada \n";
	man.set_position(200,200);
	man.draw();
	
	
	// eventos
	ALLEGRO_EVENT_QUEUE * events = al_create_event_queue();
	if (!events) cerr << "Error creando event queue\n";
	if (!al_install_mouse()) cerr << "Error instalando mouse\n";
	ALLEGRO_EVENT_SOURCE * mouse = al_get_mouse_event_source();
	if (!mouse) cerr << "Error creando mouse source\n";
	al_register_event_source(events, mouse);
	
	ALLEGRO_TIMER * timer = al_create_timer(1.f/FPS);
	if (!timer) cerr << "Error creando timer\n";
	al_register_event_source(events, al_get_display_event_source(display));
	al_register_event_source(events, al_get_timer_event_source(timer));
	al_start_timer(timer);
	int x=0; int y=0;
	bool repeat = true;
	while(repeat) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(events, &ev);
		// if (!ev) cerr << "Error en el mouse event\n";
		switch(ev.type) {
			case ALLEGRO_EVENT_TIMER:
				man.clear();
				man.draw();
				al_flip_display();
				// al_flip_display();
				// al_flip_display();
				// al_flip_display();
				// al_draw_bitmap(img[i], display->w / 2, display->h / 2, 0);
				break; 
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if(ev.mouse.button == 2) {
					man.move(ev.mouse.x, ev.mouse.y);
				}
				break;
			
			// case ALLEGRO_EVENT_MOUSE_AXES: 
			// 	al_clear_to_color(al_map_rgb(0,0,0));
			// 	al_draw_bitmap(img, ev.mouse.x, ev.mouse.y, 0);
			// 	al_flip_display();
			// 	break;
				
			case ALLEGRO_EVENT_DISPLAY_CLOSE:  
				repeat = false;
				break;
		}
	}
	
	// al_rest(5.0);
	
	al_destroy_event_queue(events);
	al_destroy_display(display);
	return 0;
}