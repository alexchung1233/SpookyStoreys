#ifndef ACTOR_COMPONENT_H // include guard
#define ACTOR_COMPONENT_H

class ActorComponent
{
protected:
  Actor* owner;
  void setOwner(Actor* o) {owner = o;}

public:
  virtual bool init();
  virtual void update(deltaMs);
  virtual int getComponentId();

private:
  addComponent();
  int id;

};
#endif
