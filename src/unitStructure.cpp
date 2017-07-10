/*
DEPRECATED
*/
#include "unitStructure.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

unitStructure::unitStructure(const char* dir, ALLEGRO_BITMAP * backbuffer, int max_pop, ALLEGRO_COLOR color) :
	backbuffer(backbuffer),
	max_population(max_pop),
	current_population(0),
	deleted_queue(max_pop),
	hint_index(0),
	max_unit_framesize(0)
{
	units = new Pirate[max_pop];
	for (int i = 0; i < max_pop; ++i) {
		units[i] = Pirate();
	}

	char buf[80];
	// stringstream buf;
	// buf << dir << "/units.dat";
	sprintf(buf, "%s%s", dir, "/units.dat");
	// printf("%s\n", buf);
	FILE * units_file = fopen(buf, "r");
	// ifstream units_file(buf.str());
	while(fgets(buf, MAX_NAME_LENGTH - 1, units_file) != NULL) {
	// string name;
	// while (getline(units_file, name)) {
		UnitType * u = new UnitType;
		// name.copy(u->name, MAX_NAME_LENGTH);
		// units_file.get(u->name, MAX_NAME_LENGTH);
		// cerr << "name: " << u->name << endl;
		strcpy(u->name, buf); // capaz falte \0 al final
		// buf.str(string());

		sprintf(buf, "%s/", dir);
		// string file;
		// units_file >> file;
		// cerr << "file: " << file << endl;
		// buf << dir << "/" << file;
		fscanf(units_file, "%s", &buf[strlen(dir)+1]);
		cerr << "loading " << buf << endl;
		ALLEGRO_BITMAP * bmp = al_load_bitmap(buf);
		if (!bmp) cerr << "ERROR cargando bitmap de unidad " << buf << endl;
		// ALLEGRO_BITMAP * aux = al_get_target_bitmap();
		// al_set_target_bitmap(bmp);
		// for (int x = 0; x < al_get_bitmap_width(bmp); ++x)
		// {
		// 	for (int y = 0; y < al_get_bitmap_height(bmp); ++y)
		// 	{
		// 		ALLEGRO_COLOR c = al_get_pixel(bmp, x, y);
		// 		// unsigned char r1, g1, b1, a1;
		// 		// unsigned char r2, g2, b2, a2;
		// 		if (c.r == 0 && c.g == 0 && c.b == 0 && c.a == 255) { //== al_map_rgba(0, 0, 0, 255)) {
		// 			al_put_pixel(x, y, color);
		// 		}
		// 	}
		// 	std::cerr << x << "\n";
		// }
		// al_set_target_bitmap(aux);
		// al_set_target_bitmap(backbuffer);
		// al_draw_bitmap(bmp, 0, 0, 0);
		// al_flip_display();
		// al_rest(2);
		u->bmp = bmp;
		// int fsize; float speed;
		// units_file >> fsize >> speed;
		// u->framesize = fsize;
		// u->speed = speed;
		fscanf(units_file, "%d %f", &u->framesize, &u->speed);
		types.push_back(u);
		fgetc(units_file);
		// units_file.ignore(10, '\n');
		if (max_unit_framesize < u->framesize) max_unit_framesize = u->framesize;
		std::cerr << "initialized " << u->name << " framesize: " << u->framesize << " speed: " << u->speed << std::endl;
	}
}


UnitType * unitStructure::get_type(int type) {
	return types[type];
}

// busca una posicion libre en el vector de unidades, crea una unidad ahi y devuelve el puntero
// la posicion libre la busca en la cola de unidades suprimidas, de no haber, usa una posicion nueva con hint_index
Unit * unitStructure::create_unit(int type) {
	// si esta en el maximo
	if (current_population == max_population) return NULL;
	// busco una unidad libre
	int index;
	if (deleted_queue.empty())
		index = hint_index++;
	else
		index = deleted_queue.pop();
	std::cerr << "index: " << index << std::endl;
	// units[index].create_unit(types[type], backbuffer);
	return &units[index];
}


void unitStructure::delete_unit(Unit * u) {
	// u->delete_unit();
	deleted_queue.push((int)(u - &units[0])); // OJO, capaz se rompe
}


ALLEGRO_BITMAP * unitStructure::get_backbuffer() {
	return backbuffer;
}

int unitStructure::get_max_unit_framesize() {
	return max_unit_framesize;
}

int unitStructure::get_max_population(){
	return max_population;
}

int unitStructure::get_width() {
	return al_get_bitmap_width(backbuffer);
}

int unitStructure::get_height() {
	return al_get_bitmap_height(backbuffer);
}

unitStructure::~unitStructure() {
	for (int i=0; i < types.size(); i++) {
		delete types[i];
	}
	cerr << "destruyendo unitStructure\n";
}