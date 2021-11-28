
#include "Map.hpp"
#include "libtcod.hpp"

#ifndef ROUGUELITE_BSPLISTENER
#define ROUGUELITE_BSPLISTENER

class BspListener : public ITCODBspCallback {
 private:
  Map map;
  int roomNum;
  int lastx, lasty;

 public:
  BspListener(Map& map) : map(map), roomNum(0) {}
  bool visitNode(TCODBsp* node, void* userData);
};

#endif
