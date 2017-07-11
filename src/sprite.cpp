#include <iostream>
#include "sprite.h"

Sprite::Sprite() :
	bg(al_create_bitmap(256, 256)),
	cleared(true),
	frame(0),
	framesize(256 /*TODO: unhardcode*/),
	status(IDLE),
	direction(DOWN)
	{
		if (!bg) std::cerr << "Sprite ERROR: creating bg bitmap\n";
	}

Sprite::~Sprite() {
	if (!cleared) clear();
	if (bg) al_destroy_bitmap(bg);
}

void Sprite::draw(int x, int y, bool selected) {
	if (!cleared) std::cerr << "Sprite WARNING: did not call clear before draw\n";
	cleared = false;

	al_set_target_bitmap(bg);
	al_draw_bitmap_region(backbuffer, x, y, framesize, framesize, 0, 0, 0); // save background
	frame = (frame + 1) % n_frames_of(status);
	al_set_target_bitmap(backbuffer);
	if (selected) {
		// TODO: extract and parameterize ellipse position logic
		al_draw_ellipse(x + framesize / 2, y + 5 * framesize / 6, framesize/3, framesize/6, al_map_rgb(255, 255, 255), 1);
	}
	int flag = direction >= UP_RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0;
	al_draw_bitmap_region(bitmap_of(status), current_x_offset(), current_y_offset(), framesize, framesize, x, y, flag);
	pos_x = x;
	pos_y = y;
}

void Sprite::clear(){
	if (cleared) std::cerr << "Sprite WARNING: clear called twice\n";
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
	return (x > pos_x && x < pos_x + framesize && y > pos_y && y < pos_y + framesize &&
		al_get_pixel(current_bitmap(), frame * framesize + x - pos_x, framesize * status + y - pos_y).a != 0);
}

bool Sprite::is_broadly_clicked(int x, int y) {
	return (x > pos_x && x < pos_x + framesize && y > pos_y && y < pos_y + framesize);
}

ALLEGRO_COLOR Sprite::get_pixel(int x, int y) {
	if (x > framesize || y > framesize) {
		std::cerr << "Sprite ERROR: get_pixel: value (" << x << ", " << y << ") out of range\n";
	}
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
	return frame * layout_interpreter.framesize;
}

int Sprite::current_y_offset() {
	return layout_interpreter.get_y_offset(direction);
}

ALLEGRO_BITMAP *Sprite::current_bitmap() {
	return bitmap_of(status);
}

int SpriteLayoutInterpreter::x_offsets[5] = {13 * 256, 24 * 256, 0 * 256, 8 * 256, 18 * 256};
int SpriteLayoutInterpreter::bitmap_length_by_status[5] = {5, 8, 8, 5, 6};
int SpriteLayoutInterpreter::y_offsets[8] = {0 * 256, 1 * 256, 2 * 256, 3 * 256,
								  				   4 * 256, 3 * 256, 2 * 256, 1 * 256};

ALLEGRO_BITMAP *PirateSprite::bmps[STATUS_COUNT] = {nullptr, nullptr, nullptr, nullptr, nullptr};
int PirateSprite::n_frames[STATUS_COUNT] = {0, 0, 0, 0, 0};
void PirateSprite::initialize() {
	// TODO unhardcode
	bmps[IDLE] = al_load_bitmap("res/units/pirate/pirate_idle.png");
	bmps[WALK] = al_load_bitmap("res/units/pirate/pirate_walk.png");
	bmps[ATTACK] = al_load_bitmap("res/units/pirate/pirate_attack.png");
	bmps[DIE] = al_load_bitmap("res/units/pirate/pirate_die.png");
	bmps[HIT] = al_load_bitmap("res/units/pirate/pirate_hit.png");
	for (int i = 0; i < STATUS_COUNT; ++i) {
		if (bmps[i]) {
			n_frames[i] = al_get_bitmap_width(bmps[i]) / 256 /*TODO: unhardcode*/;
		} else {
			std::cerr << "PirateSprite ERROR: failed to load bitmap " << i << "\n";
			n_frames[i] = 0;
		}
	}
}