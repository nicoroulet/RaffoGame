#include "geometry.h"

rectangle::rectangle() {}

rectangle::rectangle(int u, int d, int l, int r) : up(u), down(d), left(l), right(r) {}
rectangle rectangle::intersect(rectangle & other) {
	return rectangle(MAX(up, other.up), MIN(down, other.down), MAX(left, other.left), MIN(right, other.right));
}
bool rectangle::is_valid() {
	return ((up < down) && (left < right));
}
void rectangle::print() {
	std::cout << "up: " << up << " down: " << down << " left: " << left << " right: " << right << "\n";
}

// class drawable_rectangle
drawable_rectangle::drawable_rectangle() {
	max_width = 16;
	max_height = 16;
	cleared = true;
	horizontal = al_create_bitmap(max_width, 2);
	if (!horizontal) std::cerr<<"drawable_rectangle error: creating horizontal bitmap\n";
	vertical = al_create_bitmap(2, max_height);
	if (!vertical) std::cerr<<"drawable_rectangle error: creating vertical bitmap\n";
}

void drawable_rectangle::set_values(int u, int d, int l, int r) {
	clear();
	up = u;
	down = d;
	left = l;
	right = r;
	if (down - up > max_height) {
		while (down - up > max_height) max_height *= 2;
		al_destroy_bitmap(vertical);
		vertical = al_create_bitmap(2, max_height);
		if (!vertical) std::cerr<<"drawable_rectangle error: creating vertical bitmap\n";
	}
	if (right - left > max_width) {
		while (right - left > max_width) max_width *= 2;
		al_destroy_bitmap(horizontal);
		horizontal = al_create_bitmap(max_width, 2);
		if (!horizontal) std::cerr<<"drawable_rectangle error: creating horizontal bitmap\n";
	}
	draw();
}


void drawable_rectangle::draw() {
	// Save rectangular background
	ALLEGRO_BITMAP * bg = al_get_target_bitmap();
	al_set_target_bitmap(horizontal);
	al_draw_bitmap_region(bg, left, up, right - left + 1, 1, 0, 0, 0);
	al_draw_bitmap_region(bg, left, down, right - left + 1, 1, 0, 1, 0);

	al_set_target_bitmap(vertical);
	al_draw_bitmap_region(bg, left, up, 1, down - up + 1, 0, 0, 0);
	al_draw_bitmap_region(bg, right, up, 1, down - up + 1, 1, 0, 0);

	// Draw regtangle
	al_set_target_bitmap(bg);
	al_draw_rectangle(left+1, up+1, right+1, down+1, al_map_rgb(255, 255, 255), 1);
	cleared = false;
}

void drawable_rectangle::clear() {
	if (cleared) return;
	al_draw_bitmap_region(horizontal, 0, 0, right - left + 1, 1, left, up, 0);
	al_draw_bitmap_region(horizontal, 0, 1, right - left + 1, 1, left, down, 0);
	al_draw_bitmap_region(vertical, 0, 0, 1, down - up + 1, left, up, 0);
	al_draw_bitmap_region(vertical, 1, 0, 1, down - up + 1, right, up, 0);
	cleared = true;
}