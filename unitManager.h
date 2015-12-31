#pragma once
#include "unit.h"
#include "unitStructure.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <vector>

// Controla las unidades. 
// Permite crear unidades y maneja clicks de mouse y ticks de timer.

class unitManager {
	private:
		std::vector<unit> units;
		unitStructure uStr;
		// std::vector<std::vector<unit>::iterator> selected;
		std::vector<int> selected;
		
	public:
		unitManager(unitStructure & uStr);
		void create_unit(int type, int x, int y);
		void left_click(int x, int y);
		void tick();
};