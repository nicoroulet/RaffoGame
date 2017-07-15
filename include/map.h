#pragma once

#include "sprite.h"

#include <vector>
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class map {
    public:
        // el formato de map_file es:
            // primer linea: size
            // a continuacion la matriz de size x size que determina el mapa, con los numeros de tiles
        // tile_file es un .png que contiene una fila con todos los tiles
        map(const char * map_file, const char * tile_file);
        void display(int x, int y);
        void register_clickable(int x, int y, Sprite * s);

        int get_offset_x();
        int get_offset_y();

    private:
        std::vector<std::vector<int> > matrix;
        ALLEGRO_BITMAP * tiles;
        int size;   // medido en tiles (el mapa es cuadrado)
        int tile_size; // los tiles tambien son cuadrados

        int offset_x;
        int offset_y;
};