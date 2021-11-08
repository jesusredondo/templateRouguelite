#include "Actor.hpp"
#include "Engine.hpp"
#include "Map.hpp"
#include "libtcod.hpp"

Engine engine;

int main() {
  while (!TCODConsole::isWindowClosed()) {
    engine.update();
    engine.render();
    TCODConsole::flush();
  }
  return 0;
}
