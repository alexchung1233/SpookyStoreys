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
    
    void calculateMove(PlayerActor &player, float deltaMS, bool inSameRoom, bool holyWaterUsed);
    void setDoorLoc(sf::Vector2f doorPos);
    void isPaused(bool pause);

    void setOffice(bool isOfficeUnlocked) { this->monsterView->setOffice(isOfficeUnlocked); }
  
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