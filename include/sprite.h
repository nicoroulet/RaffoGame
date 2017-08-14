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

class PirateString {
public:
    static const char *path_keyword;
};

class GreenPirateString {
public:
    static const char *path_keyword;
};

// char unit identifier
// Would be best to have a string
template<class TypeString>
class UnitBitmap {
public:
    // Load bitmaps.
    // TODO: Might want to return success / failure
    static void initialize();
    // TODO: consider making these private and befriend Sprite
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

    int frame;

    Status status;

    Direction direction;

    int pos_x;

    int pos_y;

    ALLEGRO_BITMAP * bg;

    bool cleared;

};

template <class Bitmap>
class Sprite : public SpriteBase {
protected:
    virtual ALLEGRO_BITMAP *current_bitmap() override {
        return Bitmap::bmps[status];
    }

    virtual int current_n_frames() override {
        return Bitmap::n_frames[status];
    }
};

template <class TypeString>
ALLEGRO_BITMAP *UnitBitmap<TypeString>::bmps[STATUS_COUNT] =
    {nullptr, nullptr, nullptr, nullptr, nullptr};

template <class TypeString>
int UnitBitmap<TypeString>::n_frames[STATUS_COUNT] = {0, 0, 0, 0, 0};

template <class TypeString>
void UnitBitmap<TypeString>::initialize() {
    // TODO unhardcode
    char buffer [50];
    sprintf(buffer,"res/units/%s/%s_idle.png", TypeString::path_keyword,
            TypeString::path_keyword);
    bmps[IDLE] = al_load_bitmap(buffer);
    sprintf(buffer,"res/units/%s/%s_walk.png", TypeString::path_keyword,
            TypeString::path_keyword);
    bmps[WALK] = al_load_bitmap(buffer);
    sprintf(buffer,"res/units/%s/%s_attack.png", TypeString::path_keyword,
            TypeString::path_keyword);
    bmps[ATTACK] = al_load_bitmap(buffer);
    sprintf(buffer,"res/units/%s/%s_die.png", TypeString::path_keyword,
            TypeString::path_keyword);
    bmps[DIE] = al_load_bitmap(buffer);
    sprintf(buffer,"res/units/%s/%s_hit.png", TypeString::path_keyword,
            TypeString::path_keyword);
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

typedef UnitBitmap<PirateString> PirateBitmap;
typedef Sprite<PirateBitmap> PirateSprite;

typedef UnitBitmap<GreenPirateString> GreenPirateBitmap;
typedef Sprite<GreenPirateBitmap> GreenPirateSprite;
