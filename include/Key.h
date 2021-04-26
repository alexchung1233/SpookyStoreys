#ifndef KEY_H // include guard
#define KEY_H
#include <SFML/Graphics.hpp>
#include <cmath>  
#include "ItemActor.h"
#include "Position.h"
#include "Actor.h"
#include "PlayerActor.h"



using namespace std;
class Key : public ItemActor {

    public:
        Key();
        void init();
        Position position;
        Position getPosition();
        void setPosition(float x, float y);
        string interact(PlayerActor &player, DialogueBox &box);
        bool obtained();
        void use();
        bool pickedup;
    protected:
        PlayerActor *player;
        bool nextToPlayer(PlayerActor &player);
        string myDialogue;
};

#endif