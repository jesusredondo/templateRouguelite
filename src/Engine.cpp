
#include "Engine.hpp"

#include "Actor.hpp"
#include "Map.hpp"

Engine::Engine() {
  TCODConsole::initRoot(MAPA_ANCHO, MAPA_ALTO, "libtcod C++ tutorial", false);
  player = new Actor(40, 25, '@', TCODColor::white);
  actors.push(player);
  actors.push(new Actor(60, 13, '@', TCODColor::yellow));
  map = new Map(MAPA_ANCHO, MAPA_ALTO);
}

Engine::~Engine() {
  actors.clearAndDelete();
  delete map;
}

void Engine::update() {
  TCOD_key_t key;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
  switch (key.vk) {
    case TCODK_UP:
      if (!map->isWall(player->x, player->y - 1)) {
        player->y--;
      }
      break;
    case TCODK_DOWN:
      if (!map->isWall(player->x, player->y + 1)) {
        player->y++;
      }
      break;
    case TCODK_LEFT:
      if (!map->isWall(player->x - 1, player->y)) {
        player->x--;
      }
      break;
    case TCODK_RIGHT:
      if (!map->isWall(player->x + 1, player->y)) {
        player->x++;
      }
      break;
    default:
      break;
  }
}

void Engine::render() {
  TCODConsole::root->clear();
  // Pintar el mapa
  map->render();
  // Y los actores:
  // TCODList guarda punteros a actores. Como actors.begin devuelve un puntero a el primer elemento, en verdad tenemos
  // un puntero a un puntero. Con (*iterator) vamos de puntero a puntero de Actor hasta puntero de actor. Empleamos la
  // operación -> para acceder a ese elemento. Pinters hell in C++!
  for (Actor** iterator = actors.begin(); iterator != actors.end(); iterator++) {
    (*iterator)->render();
  }

  // Otra manera más sencilla, ya que nos estamos moviendo por todos los elementos:
  // draw the actors
  /*for (auto actor : actors) {
    actor->render();
  }
*/

  player->render();
}
