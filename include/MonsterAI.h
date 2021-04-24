#ifndef MONSTER_AI_H // include guard
#define MONSTER_AI_H

#include <iostream>

class MonsterAI
{
  public:
    float positionX;
    float positionY;

    std::string currentRoom = "Basement";
    float timeAmount = 5;
    float timeInRoom;

    std::string NextRoomList[5];

    std::string BedroomNextList[1] = {"Hallway"};
    std::string HallwayNextList[5] = {"Bedroom", "ParentRoom", "Bathroom", "Closet", "LivingRoom"};
    std::string ParentRoomNextList[1] = {"Hallway"};
    std::string ClosetNextList[1] = {"Hallway"};
    std::string BathroomNextList[1] = {"Hallway"};
    std::string LivingRoomNextList[4] = {"Hallway", "Office", "Kitchen", "Basement"};
    std::string OfficeNextList[1] = {"LivingRoom"};
    std::string KitchenNextList[1] = {"LivingRoom"};
    std::string BasementNextList[1] = {"LivingRoom"};

    MonsterAI();
    void setPosition(float x, float y);
    void calculateMove(float playerX, float playerY, float deltaMS);
    void calculateMoveInRoom(float playerX, float playerY);
    void calculateMoveOutRoom(float deltaMS);
  };

#endif /* MY_CLASS_H */
