#include "MonsterAI.h"

MonsterAI::MonsterAI() {

}
MonsterAI::MonsterAI(MonsterView &newMonsterView) {
  this->monsterView = &newMonsterView;
}

void MonsterAI::operator()(MonsterView &newMonsterView) {
  this->monsterView = &newMonsterView;
}

void MonsterAI::pause() {
  isPause = true;
}

void MonsterAI::start() {
  isPause = false;
}

bool MonsterAI::isPaused(){
  return isPause;
}

void MonsterAI::calculateMove(PlayerActor &player, float deltaMS, bool inSameRoom, bool holyWaterUsed) {
  if (!isPause){
    if(holyWaterUsed){
      monsterView->sendToBasement();
    }

    //If the room has just been changed, reset the time counter
    if (monsterView->justChangedRooms) {
      monsterView->justChangedRooms = false;
      oneDoorCounter = 0;
    }
    //If the monster and player are in the same room
    if (inSameRoom) {
      calculateMoveInRoom(player.getPosition().x, player.getPosition().y, deltaMS);
    }
    //If the monster and player are NOT in the same room
    else {
      calculateMoveOutRoom(deltaMS);
    }
  }
}

void MonsterAI::calculateMoveInRoom(float playerX, float playerY, float deltaMS) {
  //Simply move monster towards the player at all times
  if (monsterView->getMonster().getPosition().x < playerX){
    monsterView->rightPressed(deltaMS);
  }
  else {
    monsterView->leftPressed(deltaMS);
  }

  if (monsterView->getMonster().getPosition().y < playerY){
    monsterView->downPressed(deltaMS);
  }
  else {
    monsterView->upPressed(deltaMS);
  }
}

void MonsterAI::calculateMoveOutRoom(float deltaMS) {

  //Get the list of all doors in the room
  std::vector<Door> doors = monsterView->getRoom().getDoors();

  float targetX;
  float targetY;

  //If there is only one door
  if (doors.size() == 1) {
    //If it has been less than 5 seconds move towards the center of the room
    if (oneDoorCounter < 5) {
      oneDoorCounter += deltaMS;
      targetX = 400;
      targetY = 300;
    }
    //Else move towards the target door
    else {
      targetX = monsterView->newDoorX;
      targetY = monsterView->newDoorY;
    }
  }
  else {
    targetX = monsterView->newDoorX;
    targetY = monsterView->newDoorY;
  }

  if (monsterView->getMonster().getPosition().x + ((monsterView->getMonster().getSize().x)/2) < targetX){
    monsterView->rightPressed(deltaMS);
  }
  else {
    monsterView->leftPressed(deltaMS);
  }

  if (monsterView->getMonster().getPosition().y + ((monsterView->getMonster().getSize().y)/2) < targetY){
    monsterView->downPressed(deltaMS);
  }
  else {
    monsterView->upPressed(deltaMS);
  }
}

void MonsterAI::setDoorLoc(sf::Vector2f doorPos) {
  oneDoorCounter = 0;
  doorLocX = doorPos.x;
  doorLocY = doorPos.y;
}
