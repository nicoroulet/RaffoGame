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
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j]->draw(i * tile_size, j * tile_size);
        }
    }
}
