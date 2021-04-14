#ifndef HOLY_WATER_H // include guard
#define HOLY_WATER_H
#include <SFML/Graphics.hpp>
#include "ItemActor.h"
#include "Position.h"
#include "Actor.h"
#include "PlayerActor.h"



using namespace std;
class HolyWater : public ItemActor {

    public:
        HolyWater();
        void init();
        Position position;
        Position getPosition();
        void setDialogue(string dialogue);
        string getDialogue();
        string interact(PlayerActor &player);
        void setHealth(int bar);
        int getHealth();
        void useWater();
        void resetUse();
    protected:
        PlayerActor *player;
        bool nextToPlayer(PlayerActor &player);
        int health;
        string myDialogue;
};

#endif