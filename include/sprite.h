#pragma once

#include "geometry.h"

#include <vector>
#include <string>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// TODO: put these enums in a better file
enum Direction {
    DOWN,
    DOWN_LEFT,
    LEFT,
    UP_LEFT,
    UP,
    UP_RIGHT,
    RIGHT,
    DOWN_RIGHT,
    DIRECTION_COUNT // sorry about this
};

enum Status {
    IDLE,
    WALK,
    ATTACK,
    DIE,
    HIT,
    STATUS_COUNT // sorry about this too
};

// This class stores the vertical offsets for different directions.
// Consider removing if it's too trivial.
class SpriteLayoutInterpreter {
public:
    static const int framesize;
protected:
    static const int y_offsets[8];
};


// char unit identifier
// Would be best to have a string
template<char U>
class UnitBitmap {
public:
    // Load bitmaps.
    // TODO: Might want to return success / failure
    static void initialize();
protected:
    static ALLEGRO_BITMAP *bmps[STATUS_COUNT];
    static int n_frames[STATUS_COUNT];
};

// TODO: consider renaming SpriteBase to Sprite and Sprite to something else
class SpriteBase : public SpriteLayoutInterpreter {
public:
    SpriteBase();
    virtual ~SpriteBase();
    SpriteBase(const SpriteBase&) = delete;

    void draw(int x, int y, bool selected);

    void clear();

    void change_status(Status new_status);

    void change_direction(Direction new_direction);

    bool is_clicked(int x, int y);

    bool is_broadly_clicked(int x, int y);

    ALLEGRO_COLOR get_pixel(int x, int y);

    rectangle get_rectangle();

    int current_x_offset();

    int current_y_offset();

    virtual ALLEGRO_BITMAP *current_bitmap() = 0;

    virtual int current_n_frames() = 0;

    static void initialize(ALLEGRO_BITMAP * backbuff);

    static ALLEGRO_BITMAP * backbuffer;

    int frame;

    Status status;

    Direction direction;

    int pos_x;

    int pos_y;

    ALLEGRO_BITMAP * bg;

    bool cleared;

};

template <class Bitmap>
class Sprite : public SpriteBase, public Bitmap {
protected:
    virtual ALLEGRO_BITMAP *current_bitmap() override {
        return this->bmps[status];
    }

    virtual int current_n_frames() override {
        return this->n_frames[status];
    }
};

template <char U>
ALLEGRO_BITMAP *UnitBitmap<U>::bmps[STATUS_COUNT] =
    {nullptr, nullptr, nullptr, nullptr, nullptr};

template <char U>
int UnitBitmap<U>::n_frames[STATUS_COUNT] = {0, 0, 0, 0, 0};

template <char U>
void UnitBitmap<U>::initialize() {
    // TODO unhardcode
    char buffer [50];
    sprintf(buffer,"res/units/%c/%c_idle.png",U,U);
    bmps[IDLE] = al_load_bitmap(buffer);
    sprintf(buffer,"res/units/%c/%c_walk.png",U,U);
    bmps[WALK] = al_load_bitmap(buffer);
    sprintf(buffer,"res/units/%c/%c_attack.png",U,U);
    bmps[ATTACK] = al_load_bitmap(buffer);
    sprintf(buffer,"res/units/%c/%c_die.png",U,U);
    bmps[DIE] = al_load_bitmap(buffer);
    sprintf(buffer,"res/units/%c/%c_hit.png",U,U);
    bmps[HIT] = al_load_bitmap(buffer);
    for (int i = 0; i < STATUS_COUNT; ++i) {
        if (bmps[i]) {
            // TODO: unhardcode framesize
            n_frames[i] = al_get_bitmap_width(bmps[i]) / 256;
        } else {
            std::cerr << "PirateBitmap ERROR: failed to load bitmap "
                      << i << "\n";
            n_frames[i] = 0;
        }
    }
}

// Declare unit underlying types here

typedef UnitBitmap<'p'> PirateBitmap;
typedef Sprite<PirateBitmap> PirateSprite;

typedef UnitBitmap<'g'> SoldierBitmap;
typedef Sprite<SoldierBitmap> SoldierSprite;
