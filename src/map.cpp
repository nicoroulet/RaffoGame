#include "map.h"

const char *WaterTilePath::path = "res/tiles/water.png";

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
    camera.set_position(ships[0]->pos_x(), ships[0]->pos_y(), ships[0]->get_rotation());
    camera.set_transform_fixed_ship_map();
    // for (auto &row : matrix) {
    //     for (auto &tile : row) {
    //         tile->draw();
    //     }
    // }
    int tile_size = 512; // TODO unhardcode
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j]->draw(i * tile_size, j * tile_size);
        }
    }
    for (auto &ship : ships) {
        ship->draw(camera);
    }
}

void Map::add_ship(sp<Ship> ship) {
    ships.push_back(ship);
}
