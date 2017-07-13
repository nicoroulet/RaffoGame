#pragma once
#include "sprite.h"

enum mouse_state {
	normal,
	attack,
	selection,
	repair,
};

class cursor{
	
public:

	cursor(ALLEGRO_BITMAP *parent, ALLEGRO_DISPLAY *display);
	void set_cursor(ALLEGRO_DISPLAY *display, int cursor_type);
	// void normal(ALLEGRO_DISPLAY *display);
	// void attack(ALLEGRO_DISPLAY *display);
	// void selection(ALLEGRO_DISPLAY *display);
	// void repair(ALLEGRO_DISPLAY *display);

	~cursor();

private:
	mouse_state current_state;
	ALLEGRO_BITMAP *split_sprites[4];
	ALLEGRO_MOUSE_CURSOR *current_cursor;

};