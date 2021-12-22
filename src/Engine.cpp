#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight): fovRadius(FOVRADIOUS_INICIAL), gameStatus(STARTUP),
   screenWidth(screenWidth),screenHeight(screenHeight) {
  TCODConsole::initRoot(screenWidth,screenHeight,"Mi primer Rouguelite",false);

  //Jugador
  player = new Actor(25, 25, '@',"player", TCODColor::yellow);
  player->destructible=new PlayerDestructible(30,2,"Tu cadaver");
  player->attacker=new Attacker(5);
  player->ai = new PlayerAi();
  actors.push(player);



  map = new Map(ANCHO_MAPA, ALTO_MAPA);
  gui = new Gui();

  gui->message(TCODColor::red,"Bienvenido!\nDisfruta de la mazmorra, mientras puedas.");

  map->computeFov();
}

Engine::~Engine( ){
  delete map;
  delete gui;
  actors.clearAndDelete();
}


void Engine::update(){

  if(gameStatus == STARTUP){
    map->computeFov();
  }
  //Siempre que pasamos por un nuevo update, pasamos a estar en idle.
  gameStatus = IDLE;

  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&lastKey,NULL);
  player->update(); //Aquí a veces se pasa al estado NEW_TURN (cuando se mueve)

  //Actualizar el resto de actores:
  if(gameStatus == NEW_TURN){
    for(Actor* actorAux : actors){
      if(actorAux != player){
        actorAux->update();
      }
    }
    gameStatus = IDLE;
  }
}


void Engine::render(){
  TCODConsole::root->clear();
  //Mapa
  if(gameStatus == NEW_TURN){
    map->computeFov();
  }
  map->render();
  //Actores
  for(Actor* actorAux : actors){
    if(map->isInFov(actorAux->x,actorAux->y)){
      actorAux ->render();
    }

  }
  //re-renderizo el jugador:
  player->render();

  //Renderizamos la GUI:
  gui->render();


  TCODConsole::flush();
}


void Engine::sendToBack(Actor *actor) {
   actors.remove(actor);
   actors.insertBefore(actor,0);
}
