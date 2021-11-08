#include "Map.hpp"

#include "libtcod.hpp"

Map::Map(int width, int height) {
  this->width = width;
  this->height = height;

  this->tiles = new Tile[this->width * this->height];  // Más sencillo de crear

  // Para probar ponemos dos paredes:
  setWall(30, 22);
  setWall(50, 22);
}

Map::~Map() { /*delete[] tiles;*/
}

bool Map::isWall(int x, int y) const { return !tiles[x + y * width].canWalk; }

void Map::setWall(int x, int y) { tiles[x + y * width].canWalk = false; }

void Map::render() const {
  // Estáticas para que no se creen cada vez que se llama al método.
  // Constantes, no van a cambiar, también optimiza.
  static const TCODColor darkWall(0, 0, 100);
  static const TCODColor darkGround(50, 50, 150);

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      TCODConsole::root->setCharBackground(x, y, isWall(x, y) ? darkWall : darkGround);
    }
  }
}
