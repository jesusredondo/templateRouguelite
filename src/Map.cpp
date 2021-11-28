#include "Map.hpp"

#include "Actor.hpp"
#include "BSPListener.hpp"
#include "Engine.hpp"
#include "libtcod.hpp"

// Podemos añadir constantes que sólo viven dentro de este CPP:
static const int ROOM_MAX_SIZE = 12;  // Con static en un CPP sólo existen para este fichero
static const int ROOM_MIN_SIZE = 6;

Map::Map(int width, int height) {
  this->width = width;
  this->height = height;
  this->tiles = new Tile[this->width * this->height];  // Más sencillo de crear

  TCODBsp bsp(0, 0, this->width, this->height);
  bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
  BspListener listener(*this);
  bsp.traverseInvertedLevelOrder(&listener, NULL);
}

Map::~Map() { /*delete[] tiles;*/
}

bool Map::isWall(int x, int y) const { return !tiles[x + y * width].canWalk; }

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

void Map::dig(int x1, int y1, int x2, int y2) {
  if (x2 < x1) {  // Si el punto 2 está más a la izquierda, swapeamos valores
    int tmp = x2;
    x2 = x1;
    x1 = tmp;
  }
  if (y2 < y1) {  // si el punto 2 está más arriba, swapeamos valores
    int tmp = y2;
    y2 = y1;
    y1 = tmp;
  }
  // Recorremos todos los tiles entre esos dos puntos y los marcamos como "no paredes".
  for (int tilex = x1; tilex <= x2; tilex++) {
    for (int tiley = y1; tiley <= y2; tiley++) {
      tiles[tilex + tiley * width].canWalk = true;
    }
  }
}

void Map::createRoom(bool first, int x1, int y1, int x2, int y2) {
  dig(x1, y1, x2, y2);  // Agujereamos
  if (first) {
    // Si viene a verdadero es que es la primera habitación y hay que colocar al actor principal
    engine.player->x = (x1 + x2) / 2;
    engine.player->y = (y1 + y2) / 2;
  } else {
    // Si no se coloca a un NPC de amarillo
    TCODRandom* rng = TCODRandom::getInstance();
    if (rng->getInt(0, 3) == 0) {
      engine.actors.push(new Actor((x1 + x2) / 2, (y1 + y2) / 2, '@', TCODColor::yellow));
    }
  }
}
