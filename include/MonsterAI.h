#ifndef MONSTER_AI_H // include guard
#define MONSTER_AI_H
#include "MonsterView.h"
#include "PlayerActor.h"
//#include <iostream>

class MonsterAI
{
  public:
    MonsterAI();

    MonsterView* monsterView;

    MonsterAI(MonsterView &newMonsterView);
    void operator()(MonsterView &newMonsterView);
    void calculateMove(PlayerActor &player, float deltaMS, std::string playerLevel, bool inSameRoom, bool holyWaterUsed);
    void calculateMoveInRoom(float playerX, float playerY, float deltaMS);
    void calculateMoveOutRoom(float deltaMS);

    void setDoorLoc(sf::Vector2f doorPos);

    float doorLocX;
    float doorLocY;

    float oneDoorCounter = 0;

    bool isPause;

    void isPaused(bool pause);
};

#endif /* MY_CLASS_H */

    /*
    float positionX;
    float positionY;

    std::string currentRoom = "Basement";
    float timeAmount = 1;
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
    void calculateMove(float playerX, float playerY, float deltaMS, std::string playerLevel);
    void calculateMoveInRoom(float playerX, float playerY);
    void calculateMoveOutRoom(float deltaMS);

    std::string getCurrentRoom();
*/
