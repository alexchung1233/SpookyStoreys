#ifndef HOLY_WATER_H // include guard
#define HOLY_WATER_H
#include <SFML/Graphics.hpp>
#include <cmath>  
#include "ItemActor.h"
#include "DialogueBox.h"




using namespace std;
class HolyWater : public ItemActor {

    public:
        HolyWater();
        void init();
        Position position;
        Position getPosition();
        void setDialogue(string dialogue);
        string getDialogue();
        string interact(PlayerActor &player, DialogueBox &box);
        void setHealth(int bar);
        int getHealth();
        void useWater();
        void resetUse();
        sf::Vector2f getSize();
        void setSize(sf::Vector2f size);
        void setSize(float x, float y);
        bool nextToPlayer(PlayerActor &player);
        string myDialogue;
    protected:
        PlayerActor *player;
        int health;
        int pickedup;
        DialogueBox *box;
};

#endif