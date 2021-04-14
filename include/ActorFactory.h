#ifndef ACTOR_FACTORY_H // include guard
#define ACTOR_FACTORY_H
#include "Position.h"

class ActorFactory
{
public:
  ActorFactory();

  //have to figure out how to make actors, like making a item actor specifically
  void createActor();

private:
  int currentActorId;

protected:
  int nextId();

};
#endif
