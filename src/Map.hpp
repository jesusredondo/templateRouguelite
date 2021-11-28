

#ifndef ROUGUELITE_MAP
#define ROUGUELITE_MAP

/*Nos declaramos una estructura que nos permite guardar la info de una celda.
Por ahora es tan simple que lo guardamos en un Struct (funciona como clase pero
el acceso es público).
Tiene sentido que sea un struct en lugar de una clase porque solo guarda data, no lógica*/

struct Tile {
  bool canWalk;  // Se puede pasar por este tile?
  Tile() { this->canWalk = false; }  // Por defecto no se puede
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
  /* Esta sentenecia nos permite marcar la clase BspListener
   * como friend de Map.
   * Eso nos va a permitir acceder a los elementos privados de Map desde BspListener
   */
  friend class BspListener;

  void dig(int x1, int y1, int x2, int y2);  // Puntos inicial y final donde se taladra la habitación (esquinas)
  void createRoom(bool first, int x1, int y1, int x2, int y2);  // Gestiona la creación de las habitaciones y de los
                                                                // elementos que hay dentro
};

#endif
