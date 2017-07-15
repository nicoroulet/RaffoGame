#pragma once

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define MAX(x,y) (x < y? y : x)
#define MIN(x,y) (x > y? y : x)

class rectangle {
protected:
    int up;
    int down;
    int left;
    int right;

public:
    rectangle();
    rectangle(int u, int d, int l, int r);
    rectangle intersect(rectangle & other);
    bool is_valid();
    void print();
};

class drawable_rectangle : public rectangle {
private:
    ALLEGRO_BITMAP * horizontal;
    ALLEGRO_BITMAP * vertical;
    int max_width;
    int max_height;
    bool cleared;
public:
    drawable_rectangle();
    void set_values(int u, int d, int l, int r);
    void draw();
    void clear();

};