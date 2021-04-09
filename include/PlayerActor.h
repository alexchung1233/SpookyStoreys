#ifndef PLAYER_ACTOR_H
#define PLAYER_ACTOR_H

#include "CharacterActor.h"

class PlayerActor : public CharacterActor {
public:
  PlayerActor();
  Position position;
  sf::Vector2f velocity;
  void move(float x, float y);
};

#endif
