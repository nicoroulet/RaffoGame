#include "unitStructure.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

unitStructure::unitStructure(const char* dir, ALLEGRO_BITMAP * backbuffer) : backbuffer(backbuffer) {
	
	char buf[80];
	sprintf(buf, "%s%s", dir, "/units.dat");
	// printf("%s\n", buf);
	FILE * units = fopen(buf, "r");
	while(fgets(buf, MAX_NAME_LENGTH - 1, units) != NULL) {
		unitType u;
		strcpy(u.name, buf); // capaz falte \0 al final
		sprintf(buf, "%s/", dir);
		fscanf(units, "%s", &buf[strlen(dir)+1]);
		
		
		ALLEGRO_BITMAP * bmp = al_load_bitmap(buf);
		if (!bmp) cerr << "ERROR cargando bitmap de unidad " << buf << endl;
		u.bmp = bmp;
		
		fscanf(units, "%d %f", &u.framesize, &u.speed);
		types.push_back(u);
	}
}

unitType & unitStructure::get_type(int type) {
	return types[type];
}

unit unitStructure::create_unit(int type) {
	unit u(types[type], backbuffer);
	return u;
}

ALLEGRO_BITMAP * unitStructure::get_backbuffer() {
	return backbuffer;
}