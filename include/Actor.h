#ifndef ACTOR_H // include guard
#define ACTOR_H
#include "ActorComponent.h"
class Actor
{
public:
  void init();
  void update(deltaMs);
  ActorComponent* getComponent(componentId);

private:
  addComponent(ActorComponent* comp);
  map<ComponentId, ActorComponent*> components;

};
#endif
