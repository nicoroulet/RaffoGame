#pragma once
#include "sprite.h"
#include "geometry.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define MAX_NAME_LENGTH 16

struct unitType {
	
	char name[MAX_NAME_LENGTH];
	float speed;
	
	ALLEGRO_BITMAP * bmp;
	int framesize;
} __attribute__ ((__packed__)) ;

enum direction {
	down,
	down_left,
	left,
	up_left,
	up,
	up_right,
	right,
	down_right
};

class unit {
	// virtual int hp; 	// vida
	// virtual int attack; // ataque
	// virtual int melee;	// arm. de contacto
	// virtual int pierce; // arm. distancia
	
	private:
		sprite sprt;
		int pos_x;
		int pos_y;
		int dst_x;
		int dst_y;
		bool selected;
		
		
		unitType * type;
		unit(unit & u);
		
	public:
		unit();
		void create_unit(unitType * t, ALLEGRO_BITMAP * backbuffer);
		void delete_unit();
		
		void move(int x, int y);
		void clear();
		void draw();
		void select();
		void unselect();
		void set_position(int x, int y);
		int y();
		int x();
		bool operator<(unit & other);
		bool is_clicked(int x, int y); // la unidad esta en la posicion x, y
		bool is_broadly_clicked(int x, int y);
		bool intersects(rectangle & rect);
};