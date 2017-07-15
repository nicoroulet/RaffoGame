#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// pre: al_init_font_addon(), al_init_image_addon()
class menu {
    public:
        // el constructor recibe el filename de la imagen de fondo del menu 
        menu(char const * box_filename);
        
        ~menu();
        
        // agregar un boton
        void add_button(int x, int y, ALLEGRO_BITMAP * img, char const * text, ALLEGRO_COLOR color);
        // setear fuente para escrituras
        void set_font(char const * filename, int size);
        // mostrar menu en las coordenadas x y
        void display(int x, int y); 
        
    private:
        ALLEGRO_BITMAP * box;
        ALLEGRO_FONT * font;
        int fontsize;
};