#ifndef ACTOR_H // include guard
#define ACTOR_H
#include "ActorComponent.h"
#include "Position.h"

class Actor
{
public:
  void init();
  void update(deltaMs);

private:
  Position position;
  
};
#endif
