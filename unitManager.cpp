#include "unitManager.h"
#include <iostream>
using namespace std;

unitManager::unitManager(unitStructure & uStr) : uStr(uStr) {}

void unitManager::create_unit(int type, int x, int y) {
	unit u(uStr.get_type(type), uStr.get_backbuffer());
	// unit u = uStr.create_unit(type);
	// u.set_position(x,y);
	units.push_back(u);
	cerr << "pushed\n";
	units.back().set_position(x,y);
	// units.back().clear();
	// units.back().draw();
	
	selected.push_back(units.size()-1); // provisional: todas las unidades estan seleccionadas
	cerr << "selected\n";
	
	// selected.push_back(units.end()-1); // provisional: todas las unidades estan seleccionadas
}

void unitManager::left_click(int x, int y) {
	for (auto it = selected.begin(); it != selected.end(); ++it) {
		cerr << "moving\n";
		units[*it].move(x,y);
	}
	
	// for (auto it = units.begin(); it != units.end(); ++it) {
	// 	cerr << it-> dst_x << " " << it->dst_y << endl;
	// }
	
}

void unitManager::tick() {
	
	int i=0;
	// for (int i=units.size()-1; i>=0; i--) {
	// 	units[i].clear();
	// }
	for (auto it = units.rbegin(); it != units.rend(); ++it) {
		// cerr << i++ << " clearing\n";
		it->clear();
	}
	i=0;
	for (auto it = units.begin(); it != units.end(); ++it) {
		// cerr << i++ << " drawing\n";
		it->draw();
	}
	
}