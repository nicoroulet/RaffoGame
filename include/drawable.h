#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <iostream>
#include <vector>

#include "helpers.h"

/*
 * Generic interface for all drawable objects. Provides only a draw method.
 */

class Drawable {
public:
    // TODO: needs virtual destructor
    virtual void draw(int x, int y) = 0;
    virtual int get_width() = 0;
    virtual int get_height() = 0;
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
    virtual int get_width() override;
    virtual int get_height() override;
protected:
    static ALLEGRO_BITMAP *bitmap;
    static int width;
    static int height;
};

template <class BitmapPath>
ALLEGRO_BITMAP *Bitmap<BitmapPath>::bitmap = NULL;

template <class BitmapPath>
int Bitmap<BitmapPath>::width = 0;

template <class BitmapPath>
int Bitmap<BitmapPath>::height = 0;

template <class BitmapPath>
void Bitmap<BitmapPath>::initialize() {
    if (!bitmap) {
        bitmap = al_load_bitmap(BitmapPath::path);
    }
    if (!bitmap) {
        std::cerr << "Drawable ERROR: failed to load: "
                  << BitmapPath::path
                  << std::endl;
    } else {
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
    }
}

template <class BitmapPath>
int Bitmap<BitmapPath>::get_width() {
    return width;
}

template <class BitmapPath>
int Bitmap<BitmapPath>::get_height() {
    return height;
}
/*
 * Drawable with fixed image (no animation)
 */
template <class BitmapPath>
class SimpleDrawable : public Bitmap<BitmapPath> {
public:
    SimpleDrawable();
    virtual void draw(int x, int y) override;
};


template <class BitmapPath>
SimpleDrawable<BitmapPath>::SimpleDrawable() {}

template <class BitmapPath>
void SimpleDrawable<BitmapPath>::draw(int x, int y) {
    al_draw_bitmap(this->bitmap, x, y, 0);
}

// template <class BitmapPath>
// int SimpleDrawable<BitmapPath>::pos_x() {
//   return x;
// }

// template <class BitmapPath>
// int SimpleDrawable<BitmapPath>::pos_y() {
//   return y;
// }

// template <class BitmapPath>
// class ComposedDrawable : public Drawable {
// public:
//     ComposedDrawable(sp<Drawable> parent)
//     virtual void draw() override;
// protected:
//     void add_child(sp<Drawable> child);
//     sp<Drawable> parent;
//     std::vector<sp<Drawable>> children;
// };

// template <class BitmapPath>
// void ComposedDrawable<BitmapPath>::add_child(sp<Drawable> child) {
//     children.push_back(child);
// }

// template <class BitmapPath>
// void ComposedDrawable<BitmapPath>::draw() {
//     SimpleDrawable<BitmapPath>::draw();
//     for (auto &child : children) {
//         child->draw();
//     }
// }