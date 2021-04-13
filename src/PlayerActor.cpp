#include "PlayerActor.h"


PlayerActor::PlayerActor(){
}

void PlayerActor::init(){
  position = Position(400.f, 300.f);
  myVelocity = sf::Vector2f(50.f,50.f);
}

void PlayerActor::setVelocity(sf::Vector2f vector){
  myVelocity.x = vector.x;
  myVelocity.y = vector.y;
}

void PlayerActor::setVelocity(float x, float y){
  myVelocity.x = x;
  myVelocity.y = y;
}

sf::Vector2f PlayerActor::getVelocity(){
  return myVelocity;
}

void PlayerActor::move(){

}

Position PlayerActor::getPosition(){
  return position;
}

void PlayerActor::moveUp(float deltaMS){
  printf("here");
  position.y -= deltaMS * 10.f;
}

void PlayerActor::moveDown(float deltaMS){
  position.y += deltaMS * myVelocity.y;
}

void PlayerActor::moveLeft(float deltaMS){
  position.x -= deltaMS * myVelocity.x;
}

void PlayerActor::moveRight(float deltaMS){
  position.x += deltaMS * myVelocity.x;
}
