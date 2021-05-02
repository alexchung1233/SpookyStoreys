#ifndef MONSTER_AI_H // include guard
#define MONSTER_AI_H
#include "MonsterView.h"
#include "PlayerActor.h"
//#include <iostream>

class MonsterAI
{
  public:
    MonsterAI();

    MonsterAI(MonsterView &newMonsterView);
    void operator()(MonsterView &newMonsterView);
    
    void calculateMove(PlayerActor &player, float deltaMS, std::string playerLevel, bool inSameRoom, bool holyWaterUsed);
    void setDoorLoc(sf::Vector2f doorPos);
    void isPaused(bool pause);
  
  private:
    void calculateMoveInRoom(float playerX, float playerY, float deltaMS);
    void calculateMoveOutRoom(float deltaMS);

    MonsterView* monsterView;

    float doorLocX;
    float doorLocY;

    bool isPause;
    float oneDoorCounter = 0;
};

#endif /* MY_CLASS_H */