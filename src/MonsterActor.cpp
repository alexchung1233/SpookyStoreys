#include "MonsterActor.h"


MonsterActor::MonsterActor(){
}

void MonsterActor::init(){
  position = Position(400.f, 300.f);
  characterVelocity = sf::Vector2f(4000.f,4000.f);
  mySize = sf::Vector2f(240.f, 130.f);
}

void MonsterActor::setVelocity(sf::Vector2f vector){
  characterVelocity.x = vector.x;
  characterVelocity.y = vector.y;
}

void MonsterActor::setVelocity(float x, float y){
  characterVelocity.x = x;
  characterVelocity.y = y;
}

sf::Vector2f MonsterActor::getVelocity(){
  return characterVelocity;
}

void MonsterActor::move(){

}

void MonsterActor::setPosition(float x, float y){
  position.x = x;
  position.y = y;
}

Position MonsterActor::getPosition(){
  return position;
}

void MonsterActor::moveUp(float deltaMS){
  position.y -= deltaMS * characterVelocity.y;
}

void MonsterActor::moveDown(float deltaMS){
  position.y += deltaMS * characterVelocity.y;
}

void MonsterActor::moveLeft(float deltaMS){
  position.x -= deltaMS * characterVelocity.x;
}

void MonsterActor::moveRight(float deltaMS){
  position.x += deltaMS * characterVelocity.x;
}

void MonsterActor::setSize(sf::Vector2f size){
  mySize.x = size.x;
  mySize.y = size.y;

}

void MonsterActor::setSize(float x, float y){
  mySize.x = x;
  mySize.y = y;
}

sf::Vector2f MonsterActor::getSize(){
  return mySize;
}
