#include <iostream>
#include "sprite.h"

sprite::sprite(): bmp(NULL), backbuffer(NULL), bg(NULL), frame(0), status(0), cleared(0), n(0) {}
	
// sprite::sprite(const sprite & s) : bmp(s.bmp), backbuffer(s.backbuffer), size(s.size), n(s.n), frame(0), status(0), cleared(s.cleared) {
// 	bg = al_clone_bitmap(s.bg);
// 	// bg = al_create_bitmap(size, size);
// 	if (!bg) std::cerr << "Sprite ERROR: creando bg bitmap\n";
// 	std::cerr << "copyyyyyyyyyyyyyyyyyy!\n";

	
// 	// al_set_target_bitmap(bg);
// 	// al_draw_bitmap_region(s.bg, 0, 0, size, size, 0, 0, 0);
// 	// al_set_target_bitmap(backbuffer);

// }

void sprite::create_sprite(ALLEGRO_BITMAP* bitmap, ALLEGRO_BITMAP * backbuff, int framesize) {
	std::cerr << "creating sprite ....";
	bmp = bitmap;
	backbuffer = backbuff;
	size = framesize;
	frame = 0;
	status = 0;
	cleared = true;
	n = al_get_bitmap_width(bmp) / size;
	std::cerr << "gotit" << framesize;
	// bg = al_create_bitmap(size, size);
	
	bg = al_create_bitmap(size, size);
	if (!bg) std::cerr << "Sprite ERROR: creando bg bitmap\n";
	std::cerr << "created sprite\n";
}

void sprite::delete_sprite() {
	if (!cleared) clear();
	if (bg) al_destroy_bitmap(bg);
}

sprite::~sprite() {
}

// dibujar siguiente fotograma en pos x, y
void sprite::draw(int x, int y, bool selected) {
	// std::cerr << "cleared " << cleared << std::endl;
	if (!cleared) std::cerr << "Sprite: no se llamo a clear antes de draw!\n";
	cleared = false;
	
	al_set_target_bitmap(bg);
	al_draw_bitmap_region(backbuffer, x /*- size / 2*/, y/* - size / 2*/, size, size, 0, 0, 0); // guardo background
	frame = (frame + 1) % n;
	al_set_target_bitmap(backbuffer);
	if (selected) {
		al_draw_ellipse(x + size / 2, y + 5 * size / 6, size/3, size/6, al_map_rgb(255, 255, 255), 1);
	}
	al_draw_bitmap_region(bmp, frame * size, size * status, size, size, x /*- size / 2*/, y /*- size / 2*/, 0);
	pos_x = x;
	pos_y = y;
	
	
	// std::cerr << " drawing frame " << frame << "in pos " << frame * size << " " << size * status << " " << size << " " << size << " " << x - size / 2 << " " << y - size / 2 << " \n";
	
} 

// borrar ultimo fotograma
// Importante: llamar a clear de varios sprites en el orden inverso a draw
void sprite::clear(){
	if (cleared) std::cerr << "Sprite: se llamo 2 veces seguidas a clear!\n";
	cleared = true;
	al_set_target_bitmap(backbuffer);
	al_draw_bitmap_region(bg, 0, 0, size, size, pos_x /*- size/2*/, pos_y /*- size/2*/, 0);
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

bool sprite::is_clicked(int x, int y) {
	std::cerr << "clicking " << x << " " << y;
	if (x > pos_x && x < pos_x + size && y > pos_y && y < pos_y + size) std::cerr << "alpha " << al_get_pixel(bmp, frame * size + x, size * status + y).g << " " << x << " " << y << " \n";
	return (x > pos_x && x < pos_x + size && y > pos_y && y < pos_y + size && 
		al_get_pixel(bmp, frame * size + x - pos_x, size * status + y - pos_y).a != 0);
}

bool sprite::is_broadly_clicked(int x, int y) {
	return (x > pos_x && x < pos_x + size && y > pos_y && y < pos_y + size);
}

ALLEGRO_COLOR sprite::get_pixel(int x, int y) {
	if (x > size || y > size) std::cerr << "ERROR: get_pixel: valor (" << x << ", " << y << ") fuera de rango\n";
	return al_get_pixel(bmp, frame * size + x, size * status + y);
}

int sprite::get_size() {
	return size;
}

rectangle sprite::get_rectangle() {
	return rectangle(pos_y, pos_y + size, pos_x, pos_x + size);
}