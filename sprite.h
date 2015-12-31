#pragma once

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


class sprite {
	private:
		
		ALLEGRO_BITMAP* bmp;
		ALLEGRO_BITMAP * backbuffer;
		int size;
		
		int frame;  // numero de frame actual
		int n;      // indice maximo de frame
		int status; // status: un indice de estado, permite distintas secuencias graficas para un mismo objeto 
		
		int pre_x;
		int pre_y;
		ALLEGRO_BITMAP * bg; // background
		
		bool cleared;
	
	public:
		sprite(ALLEGRO_BITMAP* bitmap, ALLEGRO_BITMAP * backbuffer, int size);
		sprite(const sprite & s);
		~sprite();
		
		// dibujar siguiente fotograma en pos x, y
		void draw(int x, int y); 
		
		// borrar ultimo fotograma
		// Importante: llamar a clear de varios sprites en el orden inverso a draw
		void clear();
		
		void change_status(int new_status);
			
};