#include "unit.h"
#include "fastsqrt.h"

#include <iostream>

unit::unit(unitType & type, ALLEGRO_BITMAP * backbuffer) :
	sprt(type.bmp, backbuffer, type.framesize), type(type) {}
	
unit::unit(const unit & u) : sprt(u.sprt), type(u.type), pos_x(u.pos_x), pos_y(u.pos_y), dst_x(u.dst_x), dst_y(u.dst_y) {}

void unit::move(int x, int y) {
	dst_x = x;
	dst_y = y;
	float d_x = dst_x - pos_x;
	float d_y = dst_y - pos_y;
	float tang = d_y / (d_x + 0.0001f);
	if (tang < 0) tang = - tang;
	state status;
	if (tang < 0.41421f) {
		if (d_x > 0) status = left;
		else status = right;
	}
	else if (tang > 2.41421f) {
		if (d_y < 0) status = up;
		else status = down;
	}
	else if (d_x > 0 && d_y < 0) status = up_left;
	else if (d_x > 0 && d_y > 0) status = down_left;
	else if (d_x < 0 && d_y < 0) status = up_right;
	else status = down_right;
	sprt.change_status(status);
}

void unit::clear() {
	// if (dst_x - pos_x || dst_y - pos_y)
		sprt.clear();
}

void unit::draw() {
	float d_x = dst_x - pos_x;
	float d_y = dst_y - pos_y;
	// if (d_x || d_y) {
		float dist = fastsqrt(d_x * d_x + d_y * d_y);
		pos_x += d_x * ((type.speed<dist)? type.speed : dist) / dist;
		pos_y += d_y * ((type.speed<dist)? type.speed : dist) / dist;
		sprt.draw(pos_x, pos_y);
		std::cerr << pos_x << " " << pos_y << "\n";
	// }
	
}

void unit::set_position(int x, int y) {
	pos_x = x-1;
	pos_y = y-1;
	dst_x = x;
	dst_y = y;
	draw();
	// sprt.draw(pos_x, pos_y);
}

