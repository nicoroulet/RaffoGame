#include <iostream>
#include "sprite.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
sprite::sprite(ALLEGRO_BITMAP* bitmap, ALLEGRO_BITMAP * backbuffer, int size):
	bmp(bitmap),
	screen(backbuffer),
	size(size),
	frame(0),
	status(0)
	{
		n = al_get_bitmap_width(bmp) / size;
		bg = al_create_bitmap(size, size);
	
		if (!bg) std::cerr << "Sprite ERROR: creando bg bitmap\n";
	}

sprite::~sprite() {
	al_destroy_bitmap(bg);
}

// dibujar siguiente fotograma en pos x, y
void sprite::draw(int x, int y) {
	al_set_target_bitmap(bg);
	al_draw_bitmap_region(screen, x - size / 2, y - size / 2, size, size, 0, 0, 0); // guardo background
	frame = (frame + 1) % n;
	al_set_target_bitmap(screen);
	al_draw_bitmap_region(bmp, frame * size, size * status, size, size, x - size / 2, y - size / 2, 0);
	pre_x = x;
	pre_y = y;
} 

// borrar ultimo fotograma
// Importante: llamar a clear de varios sprites en el orden inverso a draw
void sprite::clear(){
	al_set_target_bitmap(screen);
	al_draw_bitmap_region(bg, 0, 0, size, size, pre_x - size/2, pre_y - size/2, 0);
}

void sprite::change_status(int new_status) {
	// if (status >= bmp->h / size) {
	// 	std::cerr << "Status invalido\n";
	// 	return;
	// }
	status = new_status;
	// n = al_get_bitmap_width(bmps[status]) / offset;   //guarda aca!!!
	frame = 0;
}

