#include "MonsterAI.h"


MonsterAI::MonsterAI() {
  positionX = 0;
  positionY = 0;
}

void MonsterAI::setPosition(float x, float y) {
  positionX = x;
  positionY = y;
}

void MonsterAI::calculateMove(float playerX, float playerY, float deltaMS) {
  if(currentRoom == "Bedroom"){
    calculateMoveInRoom(playerX, playerY);
  }
  else{
    calculateMoveOutRoom(deltaMS);
  }
}

void MonsterAI::calculateMoveInRoom(float playerX, float playerY) {
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
