#include "PlayerActor.h"


PlayerActor::PlayerActor(){
  Position position = Position();
  sf::Vector2f velocity = sf::Vector2f();
}

void PlayerActor::move(float x, float y){
  position.x = x;
  position.y = y;
}

void PlayerActor::move(){
  position.x += velocity.x;
  position.y += velocity.y;
}

void PlayerActor::resetVelocity(){
  velocity.x = 0;
  velocity.y = 0;
}

void PlayerActor::moveUp(float move){
  velocity.y -= move;
}

void PlayerActor::moveDown(float move){
  velocity.y += move;
}

void PlayerActor::moveLeft(float move){
  velocity.x -= move;
}

void PlayerActor::moveRight(float move){
  velocity.x += move;
}
