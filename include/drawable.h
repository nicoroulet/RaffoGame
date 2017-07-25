#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <iostream>

/*
 * Generic interface for all drawable objects. Provides only a draw method.
 */

class Drawable {
public:
    // might need virtual destructor
    virtual void draw() = 0;
};

/*
 * Specialization of drawable, initializes an allegro bitmap from the path
 * provided.
 * BitmapPath shuld be a simple class with a "static const char *path"
 * public field
 */

template <class BitmapPath>
class Bitmap : public Drawable {
public:
    static void initialize();
protected:
    static ALLEGRO_BITMAP *bitmap;
    // static int width;
    // static int height;
};

template <class BitmapPath>
ALLEGRO_BITMAP *Bitmap<BitmapPath>::bitmap = NULL;

template <class BitmapPath>
void Bitmap<BitmapPath>::initialize() {
    if (!bitmap) {
        bitmap = al_load_bitmap(BitmapPath::path);
    }
    if (!bitmap) {
        std::cerr << "Drawable ERROR: failed to load: "
                  << BitmapPath::path
                  << std::endl;
    }/* else {
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
    }*/
}
