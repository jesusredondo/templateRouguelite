
#include "libtcod.hpp"

#ifndef ROUGUELITE_ENGINE
#define ROUGUELITE_ENGINE

#define MAPA_ANCHO 80
#define MAPA_ALTO 55

// No hace falta que las incluyamos, pero sí tenemos que definirlos para que sepa el compilador que existe
// Más tarde se definirán:

class Actor;
class Map;

class Engine {
 public:
  TCODList<Actor*> actors;
  Actor* player;
  Map* map;

  Engine();
  ~Engine();
  void update();
  void render();
};

extern Engine engine;  // Variable global para cualquiera que incluya esta cabecera

#endif
