#include "main.hpp"

Attacker::Attacker(float power) : power(power) {
}

void Attacker::attack(Actor *owner, Actor *target) {
  //Si el otro es destructible y no está muerto.
   if ( target->destructible && !target->destructible->isDead() ) {
     //Pintamos los logs de mensajes (cuestionable que sea aquí)
      if ( this->power - target->destructible->defense > 0 ) { //Si se hace algo de daño_
          int danioInflingido = this->power - target->destructible->defense;
          std::cout<<owner->name<<" ataca exitosamente a "<<target->name<<", restándo "<<danioInflingido<<std::endl;
          engine.gui->message(owner==engine.player ? TCODColor::red : TCODColor::lightGrey,"%s ataca exitosamente a %s con %d de danio.", owner->name.c_str(), target->name.c_str(), danioInflingido);
      } else {
        engine.gui->message(TCODColor::lightGrey,"%s  ataca sin éxito a  %s!", owner->name.c_str(), target->name.c_str());
      }
      target->destructible->takeDamage(target,this->power);
   } else {
     engine.gui->message(TCODColor::lightGrey,"%s no puede atacar a %s.",owner->name.c_str(),target->name.c_str());
   }
}
