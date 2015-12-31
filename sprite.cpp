#include <iostream>
#include "sprite.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
sprite::sprite(ALLEGRO_BITMAP* bitmap, ALLEGRO_BITMAP * backbuffer, int size):
	bmp(bitmap),
	backbuffer(backbuffer),
	size(size),
	frame(0),
	status(0),
	cleared(true)
	{
		n = al_get_bitmap_width(bmp) / size;
		bg = al_create_bitmap(size, size);
	
		if (!bg) std::cerr << "Sprite ERROR: creando bg bitmap\n";
		std::cerr << "createeeeeeeeee!\n";

	}
	
sprite::sprite(const sprite & s) : bmp(s.bmp), backbuffer(s.backbuffer), size(s.size), n(s.n), frame(0), status(0), cleared(s.cleared) {
	bg = al_create_bitmap(size, size);
	if (!bg) std::cerr << "Sprite ERROR: creando bg bitmap\n";
	std::cerr << "copyyyyyyyyyyyyyyyyyy!\n";

	// bg = al_clone_bitmap(s.bg);
	
	// al_set_target_bitmap(bg);
	// al_draw_bitmap_region(s.bg, 0, 0, size, size, 0, 0, 0);
	// al_set_target_bitmap(backbuffer);

}

sprite::~sprite() {
	if (!cleared) clear();
	std::cerr << "kill hiiiiiiim!\n";
	if (bg) al_destroy_bitmap(bg);
	std::cerr << "killed!\n";
}

// dibujar siguiente fotograma en pos x, y
void sprite::draw(int x, int y) {
	std::cerr << "cleared " << cleared << std::endl;
	if (!cleared) std::cerr << "Sprite: no se llamo a clear antes de draw!\n";
	cleared = false;
	
	al_set_target_bitmap(bg);
	al_draw_bitmap_region(backbuffer, x - size / 2, y - size / 2, size, size, 0, 0, 0); // guardo background
	frame = (frame + 1) % n;
	al_set_target_bitmap(backbuffer);
	al_draw_bitmap_region(bmp, frame * size, size * status, size, size, x - size / 2, y - size / 2, 0);
	pre_x = x;
	pre_y = y;
} 

// borrar ultimo fotograma
// Importante: llamar a clear de varios sprites en el orden inverso a draw
void sprite::clear(){
	if (cleared) std::cerr << "Sprite: se llamo 2 veces a clear!\n";
	cleared = true;
	al_set_target_bitmap(backbuffer);
	al_draw_bitmap_region(bg, 0, 0, size, size, pre_x - size/2, pre_y - size/2, 0);
}

void sprite::change_status(int new_status) {
	// if (status >= bmp->h / size) {
	// 	std::cerr << "Status invalido\n";
	// 	return;
	// }
	status = new_status;
	// n = al_get_bitmap_width(bmps[status]) / offset;   //guarda aca!!!
	// frame = 0;
}

