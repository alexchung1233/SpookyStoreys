#ifndef PLAYER_ACTOR_H
#define PLAYER_ACTOR_H

#include "CharacterActor.h"

class PlayerActor : public CharacterActor {
public:
  PlayerActor();
  void init();
  Position position;
  sf::Vector2f velocity;
  void setVelocity(sf::Vector2f vector);
  void setVelocity(float x, float y);
  sf::Vector2f getVelocity();
  Position getPosition();
  void move();
  void moveUp(float deltaMS);
  void moveDown(float deltaMS);
  void moveLeft(float deltaMS);
  void moveRight(float deltaMS);

};

#endif
