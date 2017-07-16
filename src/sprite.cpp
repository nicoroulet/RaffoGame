#include <iostream>
#include "sprite.h"

SpriteBase::SpriteBase() :
    bg(al_create_bitmap(framesize, framesize)),
    cleared(true),
    frame(0),
    status(IDLE),
    direction(DOWN)
    {
        if (!bg) std::cerr << "SpriteBase ERROR: creating bg bitmap\n";
    }

SpriteBase::~SpriteBase() {
    if (!cleared) clear();
    if (bg) al_destroy_bitmap(bg);
}

void SpriteBase::draw(int x, int y, bool selected) {
    if (!cleared)
        std::cerr << "SpriteBase WARNING: did not call clear before draw\n";
    cleared = false;

    al_set_target_bitmap(bg);
    // Save background
    al_draw_bitmap_region(backbuffer, x, y, framesize, framesize, 0, 0, 0);
    frame = (frame + 1) % current_n_frames();
    al_set_target_bitmap(backbuffer);
    if (selected) {
        // TODO: extract and parameterize ellipse position logic
        al_draw_ellipse(x + framesize / 2, y + 5 * framesize / 6, framesize/3,
                        framesize/6, al_map_rgb(255, 255, 255), 1);
    }
    int flag = direction >= UP_RIGHT ? ALLEGRO_FLIP_HORIZONTAL : 0;
    al_draw_bitmap_region(current_bitmap(), current_x_offset(),
        current_y_offset(), framesize, framesize, x, y, flag);
    pos_x = x;
    pos_y = y;
}

void SpriteBase::clear(){
    if (cleared) std::cerr << "SpriteBase WARNING: clear called twice\n";
    cleared = true;
    al_set_target_bitmap(backbuffer);
    al_draw_bitmap_region(bg, 0, 0, framesize, framesize, pos_x, pos_y, 0);
}

void SpriteBase::change_status(Status new_status) {
    status = new_status;
}

void SpriteBase::change_direction(Direction new_direction) {
    direction = new_direction;
}

bool SpriteBase::is_clicked(int x, int y) {
    return (x > pos_x
            && x < pos_x + framesize
            && y > pos_y
            && y < pos_y + framesize
            && al_get_pixel(current_bitmap(),
                            frame * framesize + x - pos_x,
                            framesize * status + y - pos_y).a != 0);
}

bool SpriteBase::is_broadly_clicked(int x, int y) {
    return (x > pos_x
            && x < pos_x + framesize
            && y > pos_y
            && y < pos_y + framesize);
}

ALLEGRO_COLOR SpriteBase::get_pixel(int x, int y) {
    if (x > framesize || y > framesize) {
        std::cerr << "SpriteBase ERROR: get_pixel: value (" << x
                  << ", " << y << ") out of range\n";
    }
    return al_get_pixel(current_bitmap(),
                        frame * framesize + x,
                        framesize * status + y);
}

rectangle SpriteBase::get_rectangle() {
    return rectangle(pos_y, pos_y + framesize, pos_x, pos_x + framesize);
}

ALLEGRO_BITMAP *SpriteBase::backbuffer = nullptr;

void SpriteBase::initialize(ALLEGRO_BITMAP *backbuff) {
    backbuffer = backbuff;
}

int SpriteBase::current_x_offset() {
    return frame * framesize;
}

int SpriteBase::current_y_offset() {
    return y_offsets[direction];
}

const int SpriteLayoutInterpreter::framesize = 256;
const int SpriteLayoutInterpreter::y_offsets[8] =
    {0 * 256, 1 * 256, 2 * 256, 3 * 256, 4 * 256, 3 * 256, 2 * 256, 1 * 256};

ALLEGRO_BITMAP *PirateBitmap::bmps[STATUS_COUNT] =
    {nullptr, nullptr, nullptr, nullptr, nullptr};

int PirateBitmap::n_frames[STATUS_COUNT] = {0, 0, 0, 0, 0};

void PirateBitmap::initialize() {
    // TODO unhardcode
    bmps[IDLE] = al_load_bitmap("res/units/pirate/pirate_idle.png");
    bmps[WALK] = al_load_bitmap("res/units/pirate/pirate_walk.png");
    bmps[ATTACK] = al_load_bitmap("res/units/pirate/pirate_attack.png");
    bmps[DIE] = al_load_bitmap("res/units/pirate/pirate_die.png");
    bmps[HIT] = al_load_bitmap("res/units/pirate/pirate_hit.png");
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