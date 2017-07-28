#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <set>
#include <list>
#include <type_traits>
#include <memory>

#include "unit.h"
#include "geometry.h"
#include "sorted_array.h"

// TODO: these may be unnecessary later
#include "map.h"
#include "ship.h"

// Controls units
// Handles creation, selection, movement and clock ticks

class unitManager {
private:
    struct compare {
        bool operator() (std::shared_ptr<Unit> u1,
                         std::shared_ptr<Unit> u2) const {
            return *u1 < *u2;
        }
    };
    sorted_array<std::shared_ptr<Unit>, compare> units;
    std::set<std::shared_ptr<Unit>> selected;

    int display_width;
    int display_height;
    int last_click_x;
    int last_click_y;
    bool clicked;
    drawable_rectangle rect;

    // TODO: temporary, remove from here
    Map map;
    Ship ship;

public:
    unitManager(int maxPop);
    template <class UnitType>
    void create(int x, int y);
    void right_unclick(int x, int y, bool shift);
    void left_click(int x, int y);
    void left_unclick(int x, int y, bool shift);
    void mouse_move(int x, int y);
    void turn_ship_right();
    void turn_ship_left();
    void tick(Camera &cam, CameraShot shot);
};

template <class UnitType>
void unitManager::create(int x, int y) {
    static_assert(std::is_base_of<Unit, UnitType>::value,
        "Type parameter of this class must derive from Unit");
    auto u = std::make_shared<UnitType>();
    u->set_position(x,y);
    units.insert(u);
}
