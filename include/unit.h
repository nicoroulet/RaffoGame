#pragma once
#include "sprite.h"
#include "geometry.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define MAX_NAME_LENGTH 16

struct UnitType {

	char name[MAX_NAME_LENGTH];
	float speed;

	ALLEGRO_BITMAP * bmp;
	int framesize;
} __attribute__ ((__packed__)) ;

class Unit {
public:
	// Rule of four (and a half):
	// Copy constructor. Not sure if it should be eliminated or just not used.
	Unit(Unit &u) = delete;
	// Move constructor
	// Unit(Unit &&u);
	// Assignment operator
	// Unit& operator=(Unit u) = default;
	// Swap
	// friend void swap(Unit &u1, Unit &u2);

	void create_unit(UnitType * t, ALLEGRO_BITMAP * backbuffer);
	void delete_unit();

	void move(int x, int y);
	void clear();
	void draw();
	void select();
	void unselect();
	void set_position(int x, int y);
	int y();
	int x();
	bool operator<(Unit & other);
	bool is_clicked(int x, int y); 			// check whether the unit sprite is non-transparent in pos x, y
	bool is_broadly_clicked(int x, int y);	// check whether the unit sprite is in pos x, y
	bool intersects(rectangle & rect);

protected:
	// Construct a Unit, getting the sprite
	Unit(Sprite *sprite);

	virtual ALLEGRO_BITMAP *unit_type_bitmap() = 0;
	static float speed;
	Sprite *sprite;
	int pos_x;
	int pos_y;
	int dst_x;
	int dst_y;
	bool selected;

	UnitType * type;
};

class Pirate : public Unit {
public:
	Pirate();
	// sets static values
	static void initialize();
protected:
	// stores the bitmap for the class' graphics
	static ALLEGRO_BITMAP *unit_type_bitmap_ptr;
	// retrieve the bitmap
	virtual ALLEGRO_BITMAP *unit_type_bitmap();
};