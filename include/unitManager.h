#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <set>
#include <list>
#include <type_traits>

#include "unit.h"
#include "geometry.h"
#include "sorted_array.h"

// Controls units
// Handles creation, selection, movement and clock ticks

class unitManager {
private:
	struct compare {
		bool operator() (Unit* u1, Unit* u2) const {return *u1 < *u2;}
	};
	sorted_array<Unit*, compare> units;
	std::set<Unit*> selected;

	int display_width;
	int display_height;
	int last_click_x;
	int last_click_y;
	bool clicked;
	drawable_rectangle rect;

public:
	unitManager(int maxPop);
	template <class UnitType>
	void create(int x, int y);
	void right_unclick(int x, int y, bool shift);
	void left_click(int x, int y);
	void left_unclick(int x, int y, bool shift);
	void mouse_move(int x, int y);
	void tick();
};

template <class UnitType>
void unitManager::create(int x, int y) {
	static_assert(std::is_base_of<Unit, UnitType>::value,
		"Type parameter of this class must derive from Unit");
	// FIXME: delete this new or change the way of creating units (smart poiners?)
	UnitType* u = new UnitType();
	u->set_position(x,y);
	units.insert(u);
}