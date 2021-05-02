#ifndef PAINTING_H // include guard
#define PAINTING_H
#include <SFML/Graphics.hpp>
#include <cmath>  
#include "ItemActor.h"
#include "PlayerActor.h"



using namespace std;
class Painting : public ItemActor {

    public:
        Painting() {};
        Painting(std::vector<std::string> inputVector);

        void init();
        Position getPosition();
        void setPosition(float x, float y);
        string interact(PlayerActor &player);
        sf::Vector2f getSize();
        void setSize(sf::Vector2f size);
        void setSize(float x, float y);
        bool nextToPlayer(PlayerActor &player);

    
    private:    
};

#endif