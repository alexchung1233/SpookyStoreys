#ifndef NOTE_H // include guard
#define NOTE_H
#include <SFML/Graphics.hpp>
#include <cmath>  
#include "ItemActor.h"
#include "Position.h"
#include "Actor.h"
#include "PlayerActor.h"



using namespace std;
class Note : public ItemActor {

    public:
        Note();
        void init();
        Position position;
        Position getPosition();
        void setPosition(float x, float y);
        void setDialogue(string dialogue);
        string getDialogue();
        string interact(PlayerActor &player);
        string myDialogue;
        bool read;
    protected:
        PlayerActor *player;
        bool nextToPlayer(PlayerActor &player);
};

#endif