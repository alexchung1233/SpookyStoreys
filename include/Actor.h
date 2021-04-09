#ifndef ACTOR_H // include guard
#define ACTOR_H
#include "Position.h"

class Actor
{
public:
  void init();
  void update(float deltaMs);

private:
  Position position;
  
};
#endif
