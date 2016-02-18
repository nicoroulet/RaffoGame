#pragma once
#include "unit.h"
#include "unitStructure.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <vector>
#include <set>
#include <list>

// Controla las unidades. 
// Permite crear unidades y maneja clicks de mouse y ticks de timer.

class unitManager {
	private:
		struct compare {
			bool operator() (unit* u1, unit* u2) {return u1->y() < u2->y();}
		};
		std::set<unit*, compare> units;
		std::set<unit*> selected;
		unitStructure uStr;
		
		
	public:
		unitManager(unitStructure & uStr);
		void create_unit(int type, int x, int y);
		void left_unclick(int x, int y);
		void right_click(int x, int y);
		void right_unclick(int x, int y);
		void tick();
};