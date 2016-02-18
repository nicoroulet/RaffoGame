#include "unitManager.h"
#include <iostream>
#include <set>
#include <utility>

using namespace std;



unitManager::unitManager(unitStructure & uStr) : uStr(uStr) {}

void unitManager::create_unit(int type, int x, int y) {
	// unit u(uStr.get_type(type), uStr.get_backbuffer());
	unit * u = uStr.create_unit(type);
	u->set_position(x,y);
	units.insert(u);
	
	// auto ins = units.insert(std::make_pair<unit, std::list<unit*>::iterator>(u, selected.end())).first; // ins es un iterador al par agregado
	
	// units[u] = selected.end();;
	
	// cerr << "created unit\n";
	
	// ins->first.set_position(x,y);
	// units.back().clear();
	// units.back().draw();
	
	// selected.push_back(units.size()-1); // provisional: todas las unidades estan seleccionadas
	// cerr << "selected\n";
	
	// selected.push_back(units.end()-1); // provisional: todas las unidades estan seleccionadas
}

void unitManager::left_unclick(int x, int y) {
	for (auto it = selected.begin(); it != selected.end(); ++it) {
		cerr << "moving\n";
		(*it)->move(x,y);
	}
	
	// for (auto it = units.begin(); it != units.end(); ++it) {
	// 	cerr << it-> dst_x << " " << it->dst_y << endl;
	// }
	
}

void unitManager::right_click(int x, int y) {
	
}

void unitManager::right_unclick(int x, int y) {
	selected.clear();
	
	
	
	// seleccion cabeza
	for (auto it = units.begin(); it != units.end(); ++it) {
		if ((*it)->is_clicked(x, y)) {
			selected.insert((*it));
			cerr << "selected\n";
			return;
		}
	}
	
	for (auto it = units.begin(); it != units.end(); ++it) {
		if ((*it)->is_broadly_clicked(x, y)) {
			selected.insert((*it));
			cerr << "broadly selected\n";
			return;
		}
	}
	
}

void unitManager::tick() {
	
	int i=0;
	// for (int i=units.size()-1; i>=0; i--) {
	// 	units[i].clear();
	// }
	for (auto it = units.rbegin(); it != units.rend(); ++it) {
		// cerr << i++ << " clearing\n";
		(*it)->clear();
	}
	i=0;
	for (auto it = units.begin(); it != units.end(); ++it) {
		// cerr << i++ << " drawing\n";
		(*it)->draw();
	}
	
}

// void unitManager::register_clickable(int x, int y, sprite * s) {
// 	// x, y de la pantalla, no del mapa
// 	clickables[map_x / tile_size][map_y / tile_size].emplace_back(x, y, s);
// }
