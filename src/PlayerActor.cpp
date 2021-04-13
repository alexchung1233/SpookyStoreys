#include "PlayerActor.h"


PlayerActor::PlayerActor(){
}

void PlayerActor::init(){
  position = Position(400.f, 300.f);
  myVelocity = sf::Vector2f(25.f,25.f);
  mySize = sf::Vector2f(48.f, 105.6f);
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
  position.y -= 1 * myVelocity.y;
}

void PlayerActor::moveDown(float deltaMS){
  position.y += 1 * myVelocity.y;
}

void PlayerActor::moveLeft(float deltaMS){
  position.x -= 1 * myVelocity.x;
}

void PlayerActor::moveRight(float deltaMS){
  position.x += 1 * myVelocity.x;
}

void PlayerActor::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void PlayerActor::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f PlayerActor::getSize(){
  return mySize;
}
