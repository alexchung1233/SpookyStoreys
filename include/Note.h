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
        Note() {};
        Note(vector<string> inputVector);

        void init();
        Position getPosition();
        void setPosition(float x, float y);
        string interact(PlayerActor &player);
        sf::Vector2f getSize();
        void setSize(sf::Vector2f size);
        void setSize(float x, float y);
        bool read;
    private:
        PlayerActor *player;
        bool nextToPlayer(PlayerActor &player);
};

#endif