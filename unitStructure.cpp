#include "unitStructure.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

unitStructure::unitStructure(const char* dir, ALLEGRO_BITMAP * backbuffer, int max_pop) : 
	backbuffer(backbuffer),
	max_population(max_pop),
	current_population(0),
	deleted_queue(max_pop),
	hint_index(max_pop),
	max_unit_framesize(0)
{
	units = new unit[max_pop];
	for (int i = 0; i < max_pop; ++i) {
		units[i] = unit();
	}
	
	char buf[80];
	sprintf(buf, "%s%s", dir, "/units.dat");
	// printf("%s\n", buf);
	FILE * units_file = fopen(buf, "r");
	while(fgets(buf, MAX_NAME_LENGTH - 1, units_file) != NULL) {
		unitType * u = new unitType;
		strcpy(u->name, buf); // capaz falte \0 al final
		sprintf(buf, "%s/", dir);
		fscanf(units_file, "%s", &buf[strlen(dir)+1]);
		
		ALLEGRO_BITMAP * bmp = al_load_bitmap(buf);
		// al_draw_bitmap(bmp, 0, 0, 0);
		if (!bmp) cerr << "ERROR cargando bitmap de unidad " << buf << endl;
		u->bmp = bmp;
		
		fscanf(units_file, "%d %f", &u->framesize, &u->speed);
		types.push_back(u);
		
		if (max_unit_framesize < u->framesize) max_unit_framesize = u->framesize;
		std::cerr << "initialized " << u->name << " framesize: " << u->framesize << std::endl;
	}
}


unitType * unitStructure::get_type(int type) {
	return types[type];
}

// busca una posicion libre en el vector de unidades, crea una unidad ahi y devuelve el puntero
// la posicion libre la busca en la cola de unidades suprimidas, de no haber, usa una posicion nueva con hint_index
unit * unitStructure::create_unit(int type) {
	// si esta en el maximo
	if (current_population == max_population) return NULL;
	// busco una unidad libre
	int index;
	if (deleted_queue.isEmpty()) 
		index = hint_index++;
	else
		index = deleted_queue.pop();
	
	units[index].create_unit(types[type], backbuffer);
	return &units[index];
}


void unitStructure::delete_unit(unit * u) {
	u->delete_unit();
	deleted_queue.push((int)(u - &units[0])); // OJO, capaz se rompe
}


ALLEGRO_BITMAP * unitStructure::get_backbuffer() {
	return backbuffer;
}

int unitStructure::get_max_unit_framesize() {
	return max_unit_framesize;
}


unitStructure::~unitStructure() {
	for (int i=0; i < types.size(); i++) {
		delete types[i];
	}
	cerr << "destruyendo unitStructure\n";
}