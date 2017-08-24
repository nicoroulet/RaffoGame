#include "hud.h"

HUD::HUD(int width, int height, const Camera &camera) :
    compass(),
    compass_position(margin, height - margin - compass.get_height()),
    camera(camera)
    {}

void HUD::draw() {
    compass.draw(compass_position.x, compass_position.y, camera.get_rotation());
}

const char *HUD::CompassPath::path = "res/misc/compass.png";

const int HUD::margin = 50;