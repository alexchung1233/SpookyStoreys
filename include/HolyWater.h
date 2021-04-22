#ifndef HOLY_WATER_H // include guard
#define HOLY_WATER_H
#include <SFML/Graphics.hpp>
#include <cmath>  
#include "ItemActor.h"




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

        sf::Vector2f getSize();
        void setSize(sf::Vector2f size);
        void setSize(float x, float y);
    protected:
        PlayerActor *player;
        bool nextToPlayer(PlayerActor &player);
        int health;
        string myDialogue;
};

#endif