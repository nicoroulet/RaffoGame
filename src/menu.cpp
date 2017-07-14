#include "menu.h"
#include <iostream>

menu::menu(char const * box_filename): font(NULL) {
	
	box = al_load_bitmap(box_filename);
	if (!box) std::cerr << "Menu ERROR: creando box bitmap\n";
	
}

menu::~menu() {
	if (box) al_destroy_bitmap(box);
	if (font) al_destroy_font(font);
}

void menu::add_button(int x, int y, ALLEGRO_BITMAP * img, 
					  char const * text, ALLEGRO_COLOR color) {
	ALLEGRO_BITMAP * aux = al_get_target_bitmap();
	al_set_target_bitmap(box);
	al_draw_bitmap(img, x, y, 0);
	if (!font) {
		std::cerr << "Menu ERROR (add_button): undefined font\n";
		return;
	}
	
	// al_draw_text(font, color, x + (al_get_bitmap_height(img) - fontsize) / 2, y , ALLEGRO_ALIGN_CENTRE, text);
	// al_draw_text(font, color, x, y , ALLEGRO_ALIGN_CENTRE, text);
	al_draw_text(font, 
				 color,
				 x + al_get_bitmap_width(img) / 2,
				 y + (al_get_bitmap_height(img)) / 2 - fontsize,
				 ALLEGRO_ALIGN_CENTRE,
				 text);
	al_set_target_bitmap(aux);
}

void menu::set_font(char const * filename, int size) {
	font = al_load_ttf_font(filename, size, 0);
	if (!font) std::cerr << "Menu ERROR (set font): loading font\n";
	fontsize = size;
}

void menu::display(int x, int y) {
	al_draw_bitmap(box, x, y, 0);
}