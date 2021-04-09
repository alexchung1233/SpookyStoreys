#include "PlayerActor.h"


PlayerActor::PlayerActor(){
  Position position = Position();
  sf::Vector2f velocity = sf::Vector2f();
}

void PlayerActor::move(float x, float y){
  position.x = x;
  position.y = y;
}
