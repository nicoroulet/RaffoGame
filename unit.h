#pragma once
#include "sprite.h"

// float speed = 5;

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
		int dst_x;
		int dst_y;
		
		static float speed;
		
	public:
		unit(ALLEGRO_BITMAP* bitmap, ALLEGRO_BITMAP * backbuffer, int size);
		void move(int x, int y);
		void clear();
		void draw();
		void set_position(int x, int y);
};