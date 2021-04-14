#ifndef ACTOR_H // include guard
#define ACTOR_H
#include "Position.h"
#include <string>
#include <iostream>

class Actor
{
public:
  Actor(int actorId) {actorId = id;}
  Actor(){};
  //virtual void init();
  //virtual bool update(float deltaMs);
  //virtual void destroy();

protected:
  Position position;
  int id;

};
#endif
