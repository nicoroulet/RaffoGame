#include "unit.h"
#include "fastsqrt.h"

#include <iostream>

Unit::Unit() :
	sprt(), type(NULL) {}

// Unit::Unit(Unit & u) : sprt(u.sprt), type(u.type), pos_x(u.pos_x), pos_y(u.pos_y), dst_x(u.dst_x), dst_y(u.dst_y) {}

void Unit::create_unit(UnitType * t, ALLEGRO_BITMAP * backbuffer) {
	std::cerr << "creating unit: " << t->name;
	sprt.create_sprite(t->bmp, backbuffer, t->framesize);
	type = t;
	selected = false;
	std::cerr << "... OK\n";
}

void Unit::delete_unit() {
	sprt.delete_sprite();
}

void Unit::move(int x, int y) {
	// TODO: optimize this function
	dst_x = x - sprt.get_size()/2;
	dst_y = y - sprt.get_size()/2;
	float d_x = dst_x - pos_x;
	float d_y = dst_y - pos_y;
	float tang = d_y / (d_x + 0.0001f);
	if (tang < 0) tang = - tang;
	direction status;
	if (tang < 0.41421f) {
		if (d_x > 0) status = LEFT;
		else status = RIGHT;
	}
	else if (tang > 2.41421f) {
		if (d_y < 0) status = UP;
		else status = DOWN;
	}
	else if (d_x > 0 && d_y < 0) status = UP_LEFT;
	else if (d_x > 0 && d_y > 0) status = DOWN_LEFT;
	else if (d_x < 0 && d_y < 0) status = UP_RIGHT;
	else status = DOWN_RIGHT;
	sprt.change_status(status);
}

void Unit::clear() {
	// if (dst_x - pos_x || dst_y - pos_y)
		sprt.clear();
}

void Unit::draw() {
	float d_x = dst_x - pos_x;
	float d_y = dst_y - pos_y;

	float dist = fastsqrt(d_x * d_x + d_y * d_y);
	pos_x += d_x * ((type->speed < dist)? type->speed : dist) / dist;
	pos_y += d_y * ((type->speed < dist)? type->speed : dist) / dist;
	sprt.draw(pos_x, pos_y, selected);

}

void Unit::select() {
	selected = true;
}

void Unit::unselect() {
	selected = false;
}

void Unit::set_position(int x, int y) {
	pos_x = x-1;
	pos_y = y-1;
	dst_x = x;
	dst_y = y;
	draw();
	// sprt.draw(pos_x, pos_y);
}

int Unit::y() {
	return pos_y;
}

int Unit::x() {
	return pos_x;
}

bool Unit::operator<(Unit & other) {
	return pos_y + sprt.get_size() < other.pos_y + other.sprt.get_size();
}

bool Unit::is_clicked(int x, int y) {
	return sprt.is_clicked(x, y);
}

bool Unit::is_broadly_clicked(int x, int y) {
	return sprt.is_broadly_clicked(x, y);
}

bool Unit::intersects(rectangle & rect) {
	rectangle rect2 = sprt.get_rectangle();
	return rect.intersect(rect2).is_valid();
}