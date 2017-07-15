//#include "sprite.cpp"
#include "cursor.h"
#include <iostream>

#define M_NORMAL 0
#define M_ATTACK 1
#define M_SELECT 2
#define M_REPAIR 3
#define M_WAIT   4

cursor::cursor(ALLEGRO_BITMAP *parent, ALLEGRO_DISPLAY *display){
    split_sprites[M_NORMAL] = al_create_sub_bitmap(parent,30,42,40,46);
    split_sprites[M_ATTACK] = al_create_sub_bitmap(parent,306,42,40,46);
    split_sprites[M_SELECT] = al_create_sub_bitmap(parent,236,42,40,46);
    split_sprites[M_REPAIR] = al_create_sub_bitmap(parent,512,25,40,46);
    split_sprites[M_WAIT] = al_create_sub_bitmap(parent,86,24,36,38);
    
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
    
    /*
    int x,y;
    x = al_get_mouse_state_axis(state,0);
    y = al_get_mouse_state_axis(state,1);
    */

    current_cursor = al_create_mouse_cursor(split_sprites[M_NORMAL],0,0); 
    // Why 0,0 at the end? Doesn't seem to set cursor position

    if(!al_set_mouse_cursor(display,current_cursor)) {
        std::cerr << "Error seteando cursor" << std::endl;
        exit(1);
    }
    al_show_mouse_cursor(display);
}

void cursor::set_cursor(ALLEGRO_DISPLAY *display, int cursor_type) {
    int ret_x;
    int ret_y;
    if(!al_get_mouse_cursor_position(&ret_x,&ret_y)) {
        std::cerr << "Error getting mouse cursor position" << std::endl;
        exit(1);
    }
    al_destroy_mouse_cursor(current_cursor);
    current_cursor = al_create_mouse_cursor(split_sprites[cursor_type],
                                            ret_x,
                                            ret_y);
    if(!al_set_mouse_cursor(display,current_cursor)) {
        std::cerr << "Error setting cursor" << std::endl;
        exit(1);
    }
    al_show_mouse_cursor(display);
}


// void cursor::normal(ALLEGRO_DISPLAY *display) {
//  int ret_x;
//  int ret_y;
//  if(!al_get_mouse_cursor_position(&ret_x,&ret_y)) {
//      std::cerr << "Error obteniendo posicion current_state del cursor" << std::endl;
//      exit(1);
//  }
//  current_cursor = al_create_mouse_cursor(split_sprites[M_NORMAL],ret_x,ret_y);
//  if(!al_set_mouse_cursor(display,current_cursor)) {
//      std::cerr << "Error seteando cursor" << std::endl;
//      exit(1);
//  }
//  al_show_mouse_cursor(display);
// }

// void cursor::attack(ALLEGRO_DISPLAY *display) {
//  int ret_x;
//  int ret_y;
//  if(!al_get_mouse_cursor_position(&ret_x,&ret_y)) {
//      std::cerr << "Error obteniendo posicion current_state del cursor" << std::endl;
//      exit(1);
//  }
//  current_cursor = al_create_mouse_cursor(split_sprites[M_ATTACK],ret_x,ret_y);

//  if(!al_set_mouse_cursor(display,current_cursor)) {
//      std::cerr << "Error seteando cursor" << std::endl;
//      exit(1);
//  }
//  al_show_mouse_cursor(display);
// }

// void cursor::selection(ALLEGRO_DISPLAY *display){
//  int *ret_x = new int;
//  int *ret_y = new int;
//  if(!al_get_mouse_cursor_position(ret_x,ret_y)) {
//      std::cerr << "Error obteniendo posicion current_state del cursor" << std::endl;
//      exit(1);
//  }
//  current_cursor = al_create_mouse_cursor(split_sprites[M_SELECT],*ret_x,*ret_y);

//  if(!al_set_mouse_cursor(display,current_cursor)) {
//      std::cerr << "Error seteando cursor" << std::endl;
//      exit(1);
//  }
//  delete ret_x;
//  delete ret_y;
//  al_show_mouse_cursor(display);
// }

// void cursor::repair(ALLEGRO_DISPLAY *display){
//  int *ret_x = new int;
//  int *ret_y = new int;
//  if(!al_get_mouse_cursor_position(ret_x,ret_y)) {
//      std::cerr << "Error obteniendo posicion current_state del cursor" << std::endl;
//      exit(1);
//  }
//  current_cursor = al_create_mouse_cursor(split_sprites[M_REPAIR],*ret_x,*ret_y);

//  if(!al_set_mouse_cursor(display,current_cursor)) {
//      std::cerr << "Error seteando cursor" << std::endl;
//      exit(1);
//  }
//  delete ret_x;
//  delete ret_y;
//  al_show_mouse_cursor(display);
// }

cursor::~cursor(){
    al_destroy_mouse_cursor(current_cursor);
    for(int i=0;i<4;i++){
        al_destroy_bitmap(split_sprites[i]);
    }
}