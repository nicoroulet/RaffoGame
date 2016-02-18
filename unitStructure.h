#pragma once

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "unit.h"
#include "static_queue.h"

// Tiene los datos basicos de cada tipo de unidad para crearlas mas facilmente

class unitStructure {
	public:
		unitStructure(const char* dir, ALLEGRO_BITMAP * backbuffer, int max_pop);
		~unitStructure();
		unitType * get_type(int type);
		unit * create_unit(int type);
		void delete_unit(unit * u);
		ALLEGRO_BITMAP * get_backbuffer();
		
		int get_max_unit_framesize();
	private:
		
		std::vector<unitType *> types;
		ALLEGRO_BITMAP * backbuffer;
		// std::vector<unit> units;
		unit* units;
		
		static_queue<int> deleted_queue; // posiciones deleteadas
		int hint_index; //posicion de units a partir de donde buscar una unidad valida
		int max_population;
		int current_population;
		
		int max_unit_framesize;
};

/*
en $dir/units.dat se listan las unidades con el siguiente formato:

<nombre> 
<imagen (sprite)> <frame size> <speed>
...

*/