#ifndef ACTOR_H // include guard
#define ACTOR_H
#include "ActorComponent.h"
#include "Position.h"

class Actor
{
public:
  virtual void init();
  virtual bool update(float deltaMs);
  virtual void destroy();

protected:
  Position position;
  int id;

};
#endif
