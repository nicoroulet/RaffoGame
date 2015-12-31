#pragma once
#include "sprite.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define MAX_NAME_LENGTH 16

struct unitType {
	
	char name[MAX_NAME_LENGTH];
	float speed;
	
	ALLEGRO_BITMAP * bmp;
	int framesize;
} __attribute__ ((__packed__)) ;

enum state {
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
		
		unitType type;
		
	public:
		int dst_x;
		int dst_y;
		unit(unitType & type, ALLEGRO_BITMAP * backbuffer);
		unit(const unit & u);
		void move(int x, int y);
		void clear();
		void draw();
		void set_position(int x, int y);
};