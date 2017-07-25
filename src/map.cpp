#include "map.h"

const char *WaterTilePath::path = "res/tiles/water.png";

template <class TilePath>
Tile<TilePath>::Tile(int x, int y) : x(x), y(y) {}

Map::Map(int height, int width) :
    height(height),
    width(width),
    matrix(height, std::vector<std::shared_ptr<Drawable> >(width))
{
    int tile_size = 512; // TODO unhardcode
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j] = std::make_shared<WaterTile>(i * tile_size,
                                                       j * tile_size);
        }
    }
}

void Map::draw() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j]->draw();
        }
    }
}