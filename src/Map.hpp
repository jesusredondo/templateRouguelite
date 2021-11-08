
/*Nos declaramos una estructura que nos permite guardar la info de una celda.
Por ahora es tan simple que lo guardamos en un Struct (funciona como clase pero
el acceso es público).
Tiene sentido que sea un struct en lugar de una clase porque solo guarda data, no lógica*/

struct Tile {
  bool canWalk;  // can we walk through this tile?
  Tile() : canWalk(true) {}
};

/**
 * @brief Representa un mapa de paredes.
 *
 */
class Map {
 public:
  int width, height;

  Map(int width, int height);
  ~Map();
  bool isWall(int x, int y) const;  // Preguntamos si un elemento es pared.
  void render() const;

 protected:
  Tile* tiles;
  void setWall(int x, int y);
};
