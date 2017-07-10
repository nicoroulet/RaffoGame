#pragma once

#include "geometry.h"

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// TODO: put these enums in a better file
enum Direction {
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DIRECTION_COUNT // sorry about this
};

enum Status {
	IDLE,
	WALK,
	ATTACK,
	DIE,
	RECEIVE_HIT,
	STATUS_COUNT // sorry about this too
};


// This abstract class is used to interpret different sprite layouts.
// That is, return the position and size of the different sprite sequences
// on a bitmap for the 8 directions and the different status (move, attack,
// stand, die, receive hit)
// Note: implementing only one concrete class for now
class SpriteLayoutInterpreter {
private:
	// horizontal offsets, indexed by status: idle, walk, attack, die, hit
	static /*const*/ int x_offsets[5];// = {13 * 256, 24 * 256, 0 * 256, 8 * 256, 18 * 256};
	// length (in frames) of the sprite sequence for every status
	static /*const*/ int bitmap_length_by_status[5];// = {5, 8, 8, 5, 6};
	// indexed by direction:
	// up, up right, right, down right, down, down left, left, up left
	// for now, the last three are mirrored from 3, 2 & 1
	static /*const*/ int y_offsets[8];// = {0 * 256, 1 * 256, 2 * 256, 3 * 256,
								  // 4 * 256, 3 * 256, 2 * 256, 1 * 256};
public:
	static const int framesize = 256;
	int get_x_offset(Status status) {
		// const int x_offsets[5] = {13 * 256, 24 * 256, 0 * 256, 8 * 256, 18 * 256};
		return x_offsets[status];
	}
	int get_y_offset(Direction direction) {
		// const int y_offsets[8] = {0 * 256, 1 * 256, 2 * 256, 3 * 256,
								  // 4 * 256, 3 * 256, 2 * 256, 1 * 256};
		return y_offsets[direction];
	}
	int get_bitmap_length(Status status) {
		// const int bitmap_length_by_status[5] = {5, 8, 8, 5, 6};
		return bitmap_length_by_status[status];
	}
};

class Sprite {
public:
	Sprite(/*ALLEGRO_BITMAP* bitmap*//*, int framesize*/);
	~Sprite();
	// Sprite(const Sprite & s) = delete;

	// void create_sprite(ALLEGRO_BITMAP* bitmap, ALLEGRO_BITMAP * backbuffer, int size);
	// void delete_sprite();

	// Draw next frame in position x, y.
	// Adds a selection animation if selected = true
	void draw(int x, int y, bool selected);

	// Clear last frame
	// Important: clear multiple sprites in reverse order from which they were drawn
	void clear();

	void change_status(Status new_status);
	void change_direction(Direction new_direction);

	// Check whether the unit is in visible in position x, y
	bool is_clicked(int x, int y);
	// Check whether the position x, y is contained in the unit's frame
	// (the frame is defined by the size of the sprite and is usually
	// bigger than the visible region of the unit)
	bool is_broadly_clicked(int x, int y);

	ALLEGRO_COLOR get_pixel(int x, int y);

	int get_framesize();
	rectangle get_rectangle();

	// Initialize the backbuffer (call this before attempting to render any sprites)
	static void initialize(ALLEGRO_BITMAP * backbuffer);
protected:
	int current_x_offset();
	int current_y_offset();
	ALLEGRO_BITMAP *current_bitmap();

	SpriteLayoutInterpreter layout_interpreter;

	// Bitmap with the animation to be displayed
	// ALLEGRO_BITMAP* bmp;

	/*inline*/ virtual ALLEGRO_BITMAP *bitmap_of(Status status) {
		std::cerr << "called dummy method bitmap_of\n";
		return nullptr; }
	/*inline*/ virtual int n_frames_of(Status status) {
		std::cerr << "called dummy method n_frames_of\n";
		return 0;
	}

	// Screen buffer on which all sprites are rendered
	static ALLEGRO_BITMAP * backbuffer;

	int framesize;

	int frame;  // current frame number
	// int n;      // maximum frame index
	Status status;
	Direction direction;

	int pos_x;
	int pos_y;
	ALLEGRO_BITMAP * bg; // background

	bool cleared;
};

class PirateSprite : public Sprite {
public:
	PirateSprite() : Sprite() {
		std::cerr << "create pirate sprite\n";

	}

	// Load bitmaps.
	// TODO: Might want to return success / failure
	static void initialize();
protected:
	ALLEGRO_BITMAP *bitmap_of(Status status) override {
		return bmps[status];
	}
	int n_frames_of(Status status) override {
		return n_frames[status];
	}
	static ALLEGRO_BITMAP *bmps[STATUS_COUNT];
	static int n_frames[STATUS_COUNT];
};