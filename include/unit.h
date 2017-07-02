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

enum direction {
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT
};

class Unit {
	public:
		Unit();
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
		static float speed;
		sprite sprt;
		int pos_x;
		int pos_y;
		int dst_x;
		int dst_y;
		bool selected;

		UnitType * type;
		Unit(Unit & u);
};
