#ifndef MONSTER_ACTOR_H
#define MONSTER_ACTOR_H

#include "CharacterActor.h"

class MonsterActor : public CharacterActor {
public:
  MonsterActor();
  void init();
  Position position;
  sf::Vector2f velocity;
  void setVelocity(sf::Vector2f vector);
  void setVelocity(float x, float y);
  void moveUp(float deltaMS);
  void moveDown(float deltaMS);
  void moveLeft(float deltaMS);
  void moveRight(float deltaMS);

};

#endif