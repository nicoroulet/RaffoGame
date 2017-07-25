#include "map.h"

const char *WaterTilePath::path = "res/tiles/water.png";

Map::Map(int height, int width) :
    height(height),
    width(width),
    matrix(height, std::vector<std::shared_ptr<Tile> >(width))
{
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j] = std::make_shared<WaterTile>();
        }
    }
}

void Map::draw() {
    int tile_size = 512; // TODO unhardcode
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j]->draw(i * tile_size, j * tile_size);
        }
    }
}