#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <vector>

#include <iostream>

class WaterTilePath {
public:
    static const char *path;
};

class Tile {
public:
    // might need virtual destructor
    virtual void draw(int x, int y) = 0;
};

template <class TilePath>
class ConcreteTile : public Tile {
public:
    static void initialize();
    virtual void draw(int x, int y);
private:
    static ALLEGRO_BITMAP *bitmap;
};

template <class TilePath>
ALLEGRO_BITMAP *ConcreteTile<TilePath>::bitmap = NULL;

template <class TilePath>
void ConcreteTile<TilePath>::initialize() {
    if (!bitmap) {
        std::cerr << "loading bitmap\n";
        bitmap = al_load_bitmap(TilePath::path);
        std::cerr << "loaded bitmap" << bitmap << std::endl;
    }
}

template <class TilePath>
void ConcreteTile<TilePath>::draw(int x, int y) {
    al_draw_bitmap(bitmap, x, y, 0);
}

typedef ConcreteTile<WaterTilePath> WaterTile;

class Map {
public:
    Map(int height, int width);

    void draw();
private:
    std::vector<std::vector<std::shared_ptr<Tile> > > matrix;
    int height;
    int width;
};

