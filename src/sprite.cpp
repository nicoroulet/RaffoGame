#include <iostream>
#include "sprite.h"

Sprite::Sprite(/*ALLEGRO_BITMAP* bitmap*//*, int framesize*/)
	// bg(al_create_bitmap(256, 256)),
	// bmp(bitmap),
	// cleared(true),
	// frame(0),
	// framesize(256 /*framesize*/),
	// n(al_get_bitmap_width(bmp) / framesize),
	// status(IDLE)
	{
		std::cerr << "create sprite\n";
		bg = al_create_bitmap(256, 256);
		// bmp = bitmap;
		cleared = true;
		frame = 0;
		framesize = 256 /*framesize*/;
		// if (bmp)
		// 	n = al_get_bitmap_width(bmp) / framesize;
		// else
		// 	cerr << "Sprite ERROR: tried to create sprite with null bitmap";
		status = IDLE;
		direction = DOWN;
		if (!bg) std::cerr << "Sprite ERROR: creating bg bitmap\n";
	}

Sprite::~Sprite() {
	if (!cleared) clear();
	// if (bg) al_destroy_bitmap(bg);
}

// Sprite::sprite(const sprite & s) : bmp(s.bmp), backbuffer(s.backbuffer), size(s.size), n(s.n), frame(0), status(0), cleared(s.cleared) {
// 	bg = al_clone_bitmap(s.bg);
// 	// bg = al_create_bitmap(size, size);
// 	if (!bg) std::cerr << "Sprite ERROR: creando bg bitmap\n";
// 	std::cerr << "copyyyyyyyyyyyyyyyyyy!\n";


// 	// al_set_target_bitmap(bg);
// 	// al_draw_bitmap_region(s.bg, 0, 0, size, size, 0, 0, 0);
// 	// al_set_target_bitmap(backbuffer);

// }

// void Sprite::create_sprite(ALLEGRO_BITMAP* bitmap, ALLEGRO_BITMAP * backbuff, int framesize) {
// 	std::cerr << "creating sprite ....";
// 	bmp = bitmap;
// 	backbuffer = backbuff;
// 	size = framesize;
// 	frame = 0;
// 	status = 0;
// 	cleared = true;
// 	n = al_get_bitmap_width(bmp) / size;
// 	std::cerr << "gotit" << framesize;
// 	// bg = al_create_bitmap(size, size);

// 	bg = al_create_bitmap(size, size);
// 	if (!bg) std::cerr << "Sprite ERROR: creando bg bitmap\n";
// 	std::cerr << "created sprite\n";
// }

// void Sprite::delete_sprite() {
// 	if (!cleared) clear();
// 	if (bg) al_destroy_bitmap(bg);
// }


void Sprite::draw(int x, int y, bool selected) {
	// std::cerr << "cleared " << cleared << std::endl;
	if (!cleared) std::cerr << "Sprite: no se llamo a clear antes de draw!\n";
	cleared = false;

	al_set_target_bitmap(bg);
	al_draw_bitmap_region(backbuffer, x, y, framesize, framesize, 0, 0, 0); // save background
	std::cerr << "\n" << n_frames_of(status) << "\n";
	frame = (frame + 1) % n_frames_of(status);
	al_set_target_bitmap(backbuffer);
	// if (selected) {
	// 	al_draw_ellipse(x + framesize / 2, y + 5 * framesize / 6, framesize/3, framesize/6, al_map_rgb(255, 255, 255), 1);
	// }
	int flag = direction >= UP_RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0;
	al_draw_bitmap_region(bitmap_of(status), current_x_offset(), current_y_offset(), framesize, framesize, x, y, flag);
	pos_x = x;
	pos_y = y;


	// std::cerr << " drawing frame " << frame << "in pos " << frame * framesize << " " << framesize * status << " " << framesize << " " << framesize << " " << x - framesize / 2 << " " << y - framesize / 2 << " \n";

}

void Sprite::clear(){
	if (cleared) std::cerr << "Sprite: se llamo 2 veces seguidas a clear!\n";
	cleared = true;
	al_set_target_bitmap(backbuffer);
	al_draw_bitmap_region(bg, 0, 0, framesize, framesize, pos_x /*- framesize/2*/, pos_y /*- framesize/2*/, 0);
}

void Sprite::change_status(Status new_status) {
	status = new_status;
}

void Sprite::change_direction(Direction new_direction) {
	direction = new_direction;
}

bool Sprite::is_clicked(int x, int y) {
	std::cerr << "clicking " << x << " " << y;
	// if (x > pos_x && x < pos_x + framesize && y > pos_y && y < pos_y + framesize) std::cerr << "alpha " << al_get_pixel(bmp, frame * framesize + x, framesize * status + y).g << " " << x << " " << y << " \n";
	return (x > pos_x && x < pos_x + framesize && y > pos_y && y < pos_y + framesize &&
		al_get_pixel(current_bitmap(), frame * framesize + x - pos_x, framesize * status + y - pos_y).a != 0);
}

bool Sprite::is_broadly_clicked(int x, int y) {
	return (x > pos_x && x < pos_x + framesize && y > pos_y && y < pos_y + framesize);
}

ALLEGRO_COLOR Sprite::get_pixel(int x, int y) {
	if (x > framesize || y > framesize) std::cerr << "ERROR: get_pixel: valor (" << x << ", " << y << ") fuera de rango\n";
	return al_get_pixel(current_bitmap(), frame * framesize + x, framesize * status + y);
}

int Sprite::get_framesize() {
	return framesize;
}

rectangle Sprite::get_rectangle() {
	return rectangle(pos_y, pos_y + framesize, pos_x, pos_x + framesize);
}

ALLEGRO_BITMAP *Sprite::backbuffer = NULL;

void Sprite::initialize(ALLEGRO_BITMAP *backbuff) {
	backbuffer = backbuff;
}

int Sprite::current_x_offset() {
	return frame * layout_interpreter.framesize/* + layout_interpreter.get_x_offset(status)*/;
}

int Sprite::current_y_offset() {
	return layout_interpreter.get_y_offset(direction);
}

ALLEGRO_BITMAP *Sprite::current_bitmap() {
	return bitmap_of(status);
}

/*const*/ int SpriteLayoutInterpreter::x_offsets[5] = {13 * 256, 24 * 256, 0 * 256, 8 * 256, 18 * 256};
/*const*/ int SpriteLayoutInterpreter::bitmap_length_by_status[5] = {5, 8, 8, 5, 6};
/*const*/ int SpriteLayoutInterpreter::y_offsets[8] = {0 * 256, 1 * 256, 2 * 256, 3 * 256,
								  				   4 * 256, 3 * 256, 2 * 256, 1 * 256};

ALLEGRO_BITMAP *PirateSprite::bmps[STATUS_COUNT] = {nullptr, nullptr, nullptr, nullptr, nullptr};
int PirateSprite::n_frames[STATUS_COUNT] = {0, 0, 0, 0, 0};
void PirateSprite::initialize() {
	bmps[IDLE] = al_load_bitmap("res/units/pirate/pirate_idle.png");
	bmps[1] = al_load_bitmap("res/units/pirate/pirate_walk.png");
	bmps[2] = al_load_bitmap("res/units/pirate/pirate_attack.png");
	bmps[3] = al_load_bitmap("res/units/pirate/pirate_death.png");
	bmps[4] = al_load_bitmap("res/units/pirate/pirate_hit.png");
	for (int i = 0; i < STATUS_COUNT; ++i) {
		if (bmps[i]) {
			n_frames[i] = al_get_bitmap_width(bmps[i]) / 256 /*TODO: unhardcode*/;
		} else {
			std::cerr << "PirateSprite ERROR: failed to load bitmap " << i << "\n";
			n_frames[i] = 0;
		}
	}
}