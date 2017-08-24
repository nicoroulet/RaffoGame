#include "map.h"

const char *WaterTilePath::path = "res/tiles/water.png";

Map::Map() {}

Map::Map(int height, int width) :
    height(height),
    width(width),
    matrix(height, std::vector<std::shared_ptr<Drawable> >(width))
{
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j] = std::make_shared<WaterTile>();
        }
    }
}

void Map::draw(Camera &camera) {
    // FIXME this is not the right place for this
    al_clear_to_color(al_map_rgb(0, 0, 0));
    camera.set_transform_map();
    int tile_size = 512; // TODO unhardcode
    // number of tile column where the camera is centered
    int cam_tile_x = camera.get_pos().x / tile_size;
    // number of tile row where the camera is centered
    int cam_tile_y = camera.get_pos().y / tile_size;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            /* Infinite map.
             * Wraps map rows and columns module width and height respectively,
             * closest tho cam_tile_x and cam_tile_y.
             * That is, draw width / 2 columns to the left and width / 2 to the
             * right (+-1), and the same with rows.
             */
            int x = j + (cam_tile_x / width) * width;
            if (cam_tile_x < 0) x -= width;
            if (x < cam_tile_x - width / 2) {
                x += width;
            } else if (x > cam_tile_x + width / 2) {
                x -= width;
            }
            int y = i + (cam_tile_y / height) * height;
            if (cam_tile_y < 0) y -= height;
            if (y < cam_tile_y - height / 2) {
                y += height;
            } else if (y > cam_tile_y + height / 2) {
                y -= height;
            }
            matrix[i][j]->draw(x * tile_size, y * tile_size);
        }
    }
}
