#include "unitManager.h"
#include "camera.h"
#include <iostream>
#include <set>
#include <utility>
#include <iterator>
#include <queue>
#include <math.h>

using namespace std;



unitManager::unitManager(int maxPop) :
    units(maxPop),
    clicked(false),
    map(10, 10),
    ship(200, -200) {}

void unitManager::right_unclick(int x, int y, bool shift) {
    for (auto it = selected.begin(); it != selected.end(); ++it) {
        cerr << "moving\n";
        (*it)->move(x,y);
    }
}

void unitManager::left_click(int x, int y) {
    last_click_x = x;
    last_click_y = y;
    rect.set_values(y, y, x, x);
    clicked = true;
}

void unitManager::left_unclick(int x, int y, bool shift) {
    rect.clear();
    clicked = false;

    if (!shift) {
        for (auto it = selected.begin(); it != selected.end(); ++it)
            (*it)->unselect();
        selected.clear();
    }

    if ((last_click_x == x) && (last_click_y == y)) { // Single selection
        /* TODO: implement more sophisticated selection detection
                 (grid, quad-tree, etc) */
        for (auto it = units.rbegin(); it != units.rend(); ++it) {
            if ((*it)->is_clicked(x, y)) {
                selected.insert((*it));
                (*it)->select();
                cerr << "selected\n";
                return;
            }
        }

        for (auto it = units.rbegin(); it != units.rend(); ++it) {
            if ((*it)->is_broadly_clicked(x, y)) {
                selected.insert((*it));
                (*it)->select();
                cerr << "broadly selected\n";
                return;
            }
        }
    } else { // Range selection
        for (auto it = units.rbegin(); it != units.rend(); ++it) {
            if ((*it)->intersects(rect)) {
                selected.insert((*it));
                (*it)->select();
                cerr << "range selected\n";
            }
        }
    }
}

void unitManager::mouse_move(int x, int y) {
    if (clicked) {
        rect.set_values(MIN(last_click_y, y),
                        MAX(last_click_y, y),
                        MIN(last_click_x, x),
                        MAX(last_click_x, x));
    }
}

void unitManager::tick(Camera &cam) {
    // TODO: temporary, just for testing
    auto it = units.begin();
    ship.move();
    cam.set_position(ship.pos_x(), ship.pos_y());
    cam.set_transform_ship();
    map.draw();
    ship.draw();

    // if (clicked) {
    //     rect.clear();
    // }
    // for (auto it = units.rbegin(); it != units.rend(); ++it) {
    //     (*it)->clear();
    // }
    units.resort();
    for (auto it = units.begin(); it != units.end(); ++it) {
        (*it)->draw();
    }
    if (clicked) {
        rect.draw();
    }
}
