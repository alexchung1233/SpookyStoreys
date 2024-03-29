#ifndef MONSTER_ACTOR_H
#define MONSTER_ACTOR_H

#include "CharacterActor.h"
#include "MovementStates.h"

class MonsterActor : public CharacterActor {
public:
  MonsterActor();
  void init();
  void setVelocity(sf::Vector2f vector);
  void setVelocity(float x, float y);
  sf::Vector2f getVelocity();
  void setPosition(float x, float y);
  Position getPosition();

  void move();
  void moveUp(float deltaMS);
  void moveDown(float deltaMS);
  void moveLeft(float deltaMS);
  void moveRight(float deltaMS);
  MovementStates::movementStates getMovementState();
  MovementStates::direcStates getDirectionState();
  sf::Vector2f getSize();
  void setSize(sf::Vector2f size);
  void setSize(float x, float y);

};

#endif
