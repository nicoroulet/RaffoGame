/*
DEPRECATED
*/

#pragma once

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "unit.h"
#include "static_queue.h"
// #include <queue>

// Tiene los datos basicos de cada tipo de unidad para crearlas mas facilmente

class unitStructure {
	public:
		unitStructure(const char* dir, ALLEGRO_BITMAP * backbuffer, int max_pop, ALLEGRO_COLOR color);
		~unitStructure();
		UnitType * get_type(int type);
		Unit * create_unit(int type);
		void delete_unit(Unit * u);
		ALLEGRO_BITMAP * get_backbuffer();

		int get_max_unit_framesize();
		int get_max_population();

		int get_width();
		int get_height();
	private:

		std::vector<UnitType *> types;
		ALLEGRO_BITMAP * backbuffer;
		// std::vector<Unit> units;
		Unit* units;

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