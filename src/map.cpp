#include "map.h"
#include <fstream>
#include <iostream>

using namespace std;
map::map(const char * map_file, const char * tile_file) {
	ifstream map_f(map_file);
	map_f >> size;
	matrix = vector<vector<int> >(size, vector<int>(size));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			map_f >> matrix[i][j];
		}
	}
	tiles = al_load_bitmap(tile_file);
	if (!tiles) cerr << "ERROR loading tiles bitmap\n";

}

int map::get_offset_x() {
	return offset_x;
}

int map::get_offset_y() {
	return offset_y;
}

