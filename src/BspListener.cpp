#include "BspListener.hpp"

#include "Map.hpp"

// Podemos añadir constantes que sólo viven dentro de este CPP:
static const int ROOM_MAX_SIZE = 12;  // Con static en un CPP sólo existen para este fichero
static const int ROOM_MIN_SIZE = 6;

bool BspListener::visitNode(TCODBsp* node, void* userData) {
  if (node->isLeaf()) {
    int x, y, w, h;
    // dig a room
    TCODRandom* rng = TCODRandom::getInstance();
    w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
    h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
    x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
    y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
    map.createRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);
    if (roomNum != 0) {
      // Hacer un pasillo a la última habitación
      map.dig(lastx, lasty, x + w / 2, lasty);  // Desde el punto medio de la anterior hasta el punto medio de esta,
                                                // pero sólo taladrando horizontalmente.
      map.dig(x + w / 2, lasty, x + w / 2, y + h / 2);  // Desde el punto donde lo dejamos anteiormente, hasta la mitad
                                                        // de la actual (para poder hacer el codo si fuese necesario)
    }
    lastx = x + w / 2;
    lasty = y + h / 2;
    roomNum++;
  }
  return true;
}
