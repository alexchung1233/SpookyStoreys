#include "PlayerActor.h"


PlayerActor::PlayerActor(){
}

void PlayerActor::init(){
  position = Position();
  velocity = sf::Vector2f();
}

void PlayerActor::setVelocity(sf::Vector2f vector){
  velocity.x = vector.x;
  velocity.y = vector.y;
}

void PlayerActor::setVelocity(float x, float y){
  velocity.x = x;
  velocity.y = y;
}

void PlayerActor::moveUp(float deltaMS){
  position.y -= deltaMS * velocity.y;
}

void PlayerActor::moveDown(float deltaMS){
  position.y += deltaMS * velocity.y;
}

void PlayerActor::moveLeft(float deltaMS){
  position.x -= deltaMS * velocity.x;
}

void PlayerActor::moveRight(float deltaMS){
  position.x += deltaMS * velocity.x;
}
