#include "libtcod.hpp"

#ifndef ROUGUELITE_ACTOR
#define ROUGUELITE_ACTOR

class Actor {
 public:
  int x, y;  // Posición en la consola.
  int ch;  // Carácter que se usa para representar al actor. Se utiliza un int en lugar de un char porque permite más de
           // 256 representaciones.
  TCODColor color;  // Color.que vamos a emplear.

  Actor(int x, int y, int ch, const TCODColor& color);
  void render() const;  // lo ponemos como const para que nos aseguremos que no se cambian valores en este método.
};

#endif
