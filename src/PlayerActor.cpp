#include "PlayerActor.h"


PlayerActor::PlayerActor(){
}

void PlayerActor::init(){
  position = Position(400.f, 300.f);
  characterVelocity = sf::Vector2f(8000.f,8000.f);
  mySize = sf::Vector2f(48.f, 105.6f);
}

void PlayerActor::setVelocity(sf::Vector2f vector){
  characterVelocity.x = vector.x;
  characterVelocity.y = vector.y;
}

void PlayerActor::setVelocity(float x, float y){
  characterVelocity.x = x;
  characterVelocity.y = y;
}

sf::Vector2f PlayerActor::getVelocity(){
  return characterVelocity;
}

void PlayerActor::move(){

}

Position PlayerActor::getPosition(){
  return position;
}

void PlayerActor::moveUp(float deltaMS){
  position.y -= deltaMS * characterVelocity.y;
}

void PlayerActor::moveDown(float deltaMS){
  position.y += deltaMS * characterVelocity.y;
}

void PlayerActor::moveLeft(float deltaMS){
  position.x -= deltaMS * characterVelocity.x;
}

void PlayerActor::moveRight(float deltaMS){
  position.x += deltaMS * characterVelocity.x;

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
