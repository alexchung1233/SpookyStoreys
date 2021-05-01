#include "MonsterAI.h"

MonsterAI::MonsterAI() {

}
MonsterAI::MonsterAI(MonsterView &newMonsterView) {
  this->monsterView = &newMonsterView;
}

void MonsterAI::operator()(MonsterView &newMonsterView) {
  this->monsterView = &newMonsterView;
}

void MonsterAI::calculateMove(float playerX, float playerY, float deltaMS, std::string playerLevel, bool inSameRoom) {
  if (monsterView->justChangedRooms == true) {
    monsterView->justChangedRooms = false;
    oneDoorCounter = 0;
  }
  if (inSameRoom) {
    calculateMoveInRoom(playerX, playerY, deltaMS);
  }
  else {
    calculateMoveOutRoom(deltaMS);
  }
}

void MonsterAI::calculateMoveInRoom(float playerX, float playerY, float deltaMS) {
  //playerX = playerX + 125;
  //playerY = playerY - 20;
  if (monsterView->getMonster().getPosition().x < playerX){
    monsterView->rightPressed(deltaMS);
  }
  else {
    //std::cout << "GOT TO HERE" << '\n';
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

  std::vector<Door> doors = monsterView->getRoom().getDoors();

  float playerX;
  float playerY;

  if (doors.size() == 1) {
    if (oneDoorCounter < 5) {
      oneDoorCounter += deltaMS;
      playerX = 400;
      playerY = 300;
    }
    else {
      playerX = monsterView->newDoorX;
      playerY = monsterView->newDoorY;
    }
  }
  else {
    playerX = monsterView->newDoorX;
    playerY = monsterView->newDoorY;
  }



  if (monsterView->getMonster().getPosition().x + ((monsterView->getMonster().getSize().x)/2) < playerX){
    monsterView->rightPressed(deltaMS);
  }
  else {
    //std::cout << "GOT TO HERE" << '\n';
    monsterView->leftPressed(deltaMS);
  }

  if (monsterView->getMonster().getPosition().y + ((monsterView->getMonster().getSize().y)/2) < playerY){
    monsterView->downPressed(deltaMS);
  }
  else {
    monsterView->upPressed(deltaMS);
  }

  // /monsterView->leftPressed(deltaMS);
}

void MonsterAI::setDoorLoc(float doorX, float doorY) {
  oneDoorCounter = 0;
  doorLocX = doorX;
  doorLocY = doorY;
}


  /*
  if((currentRoom == "Bedroom") && (playerLevel == "BEDROOM")){
    calculateMoveInRoom(playerX, playerY);
  }
  else if((currentRoom == "Hallway") && (playerLevel == "HALLWAY")){
    calculateMoveInRoom(playerX, playerY);
  }
  else if((currentRoom == "ParentRoom") && (playerLevel == "PARENTROOM")){
    calculateMoveInRoom(playerX, playerY);
  }
  else if((currentRoom == "Bathroom") && (playerLevel == "BATHROOM")){
    calculateMoveInRoom(playerX, playerY);
  }
  else{
    calculateMoveOutRoom(deltaMS);
  }
  */




/*
MonsterAI::MonsterAI() {
  positionX = 0;
  positionY = 0;
}

void MonsterAI::setPosition(float x, float y) {
  positionX = x;
  positionY = y;
}

std::string MonsterAI::getCurrentRoom() {
  return (currentRoom);
}

void MonsterAI::calculateMove(float playerX, float playerY, float deltaMS, std::string playerLevel) {
  if((currentRoom == "Bedroom") && (playerLevel == "BEDROOM")){
    calculateMoveInRoom(playerX, playerY);
  }
  else if((currentRoom == "Hallway") && (playerLevel == "HALLWAY")){
    calculateMoveInRoom(playerX, playerY);
  }
  else if((currentRoom == "ParentRoom") && (playerLevel == "PARENTROOM")){
    calculateMoveInRoom(playerX, playerY);
  }
  else if((currentRoom == "Bathroom") && (playerLevel == "BATHROOM")){
    calculateMoveInRoom(playerX, playerY);
  }
  else{
    calculateMoveOutRoom(deltaMS);
  }
}

void MonsterAI::calculateMoveInRoom(float playerX, float playerY) {
  playerX = playerX + 125;
  playerY = playerY - 20;
  if (positionX < playerX){
    positionX += .05;
  }
  else {
    positionX -= .05;
  }

  if (positionY < playerY){
    positionY += .05;
  }
  else {
    positionY -= .05;
  }
}

void MonsterAI::calculateMoveOutRoom(float deltaMS) {
  timeInRoom += deltaMS;
  if(timeInRoom >= timeAmount)
  {

    std::cout << currentRoom << '\n';

    int randomNum = 0;
    timeInRoom = 0;
    if(currentRoom == "Bedroom") {
      currentRoom.assign(BedroomNextList[randomNum]);
      //currentRoom = BedroomNextList[(rand() % sizeof(BedroomNextList)-1)];
    }
    else if(currentRoom == "Hallway") {
      randomNum = (rand() % 4);
      currentRoom.assign(HallwayNextList[randomNum]);
      //currentRoom = HallwayNextList[(rand() % sizeof(HallwayNextList)-1)];
    }
    else if(currentRoom == "ParentRoom") {
      currentRoom.assign(ParentRoomNextList[randomNum]);
      //currentRoom = ParentRoomNextList[(rand() % sizeof(ParentRoomNextList)-1)];
    }
    else if(currentRoom == "Bathroom") {
      currentRoom.assign(BathroomNextList[randomNum]);
      //currentRoom = BathroomNextList[(rand() % sizeof(BathroomNextList)-1)];
    }
    else if(currentRoom == "Closet") {
      currentRoom.assign(ClosetNextList[randomNum]);
      //currentRoom = ClosetNextList[(rand() % sizeof(ClosetNextList)-1)];
    }
    else if(currentRoom == "LivingRoom") {
      randomNum = (rand() % 3);
      currentRoom.assign(LivingRoomNextList[randomNum]);
      //currentRoom = LivingRoomNextList[(rand() % sizeof(LivingRoomNextList)-1)];
    }
    else if(currentRoom == "Office") {
      currentRoom.assign(OfficeNextList[randomNum]);
      //currentRoom = OfficeNextList[(rand() % sizeof(OfficeNextList)-1)];
    }
    else if(currentRoom == "Kitchen") {
      currentRoom.assign(KitchenNextList[randomNum]);
    }
    else if(currentRoom == "Basement") {
      currentRoom.assign(BasementNextList[randomNum]);

    }

    //std::cout << currentRoom << '\n';

    //currentRoom = NextRoomList[(rand() % len(NextRoomList))];

  }
}

*/
