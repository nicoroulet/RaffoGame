#pragma once

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "unit.h"

// Tiene los datos basicos de cada tipo de unidad para crearlas mas facilmente

class unitStructure {
	public:
		unitStructure(const char* dir, ALLEGRO_BITMAP * backbuffer);
		unitType & get_type(int type);
		unit create_unit(int type);
		ALLEGRO_BITMAP * get_backbuffer();
	private:
		
		std::vector<unitType> types;
		ALLEGRO_BITMAP * backbuffer;
	
};

/*
en $dir/units.dat se listan las unidades con el siguiente formato:

<nombre> 
<imagen (sprite)> <frame size> <speed>


*/