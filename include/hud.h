#pragma once

#include "camera.h"
#include "drawable.h"
#include "geometry.h"

class HUD {
public:
    HUD(int width, int height, const Camera &camera);
    void draw();

    class CompassPath {
    public:
        static const char *path;

    };
    typedef RotableDrawable<CompassPath> Compass;
private:
    Compass compass;
    const Camera &camera;
    Vector2D compass_position;
    static const int margin;
};
