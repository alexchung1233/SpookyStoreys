#include "MonsterActor.h"


MonsterActor::MonsterActor(){
  Position position = Position();
  sf::Vector2f velocity = sf::Vector2f();
}

void MonsterActor::setVelocity(sf::Vector2f vector){
  velocity.x = vector.x;
  velocity.y = vector.y;
}

void MonsterActor::setVelocity(float x, float y){
  velocity.x = x;
  velocity.y = y;
}

void MonsterActor::moveUp(float deltaMS){
  position.y -= deltaMS * velocity.y;
}

void MonsterActor::moveDown(float deltaMS){
  position.y += deltaMS * velocity.y;
}

void MonsterActor::moveLeft(float deltaMS){
  position.x -= deltaMS * velocity.x;
}

void MonsterActor::moveRight(float deltaMS){
  position.x += deltaMS * velocity.x;
}