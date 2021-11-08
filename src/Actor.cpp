#include "Actor.hpp"

Actor::Actor(int x, int y, int ch, const TCODColor& color) {
  this->x = x;
  this->y = y;
  this->ch = ch;
  this->color = color;
}

void Actor::render() const {
  TCODConsole::root->setChar(x, y, ch);  // Cambia un carácter por otro en la consola
  TCODConsole::root->setCharForeground(x, y, color);  // Cambia el color del carácter en esa posición
}
