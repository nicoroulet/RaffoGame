#pragma once
#include "unit.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "geometry.h"
#include "sorted_array.h"
#include <vector>
#include <set>
#include <list>

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
    // template <class UnitType>
    void create_pirate(int x, int y);
    void right_unclick(int x, int y, bool shift);
    void left_click(int x, int y);
    void left_unclick(int x, int y, bool shift);
    void mouse_move(int x, int y);
    void tick();
};