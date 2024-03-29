#ifndef HOLY_WATER_H // include guard
#define HOLY_WATER_H
#include <SFML/Graphics.hpp>
#include <cmath>  
#include <string>
#include <vector>
#include "ItemActor.h"
#include "DialogueBox.h"

using namespace std;
class HolyWater : public ItemActor {

    public:
        HolyWater(std::vector<std::string> inputVector);
        void init();
        Position getPosition();
        string interact(PlayerActor &player);

        sf::Vector2f getSize();
        void setSize(sf::Vector2f size);
        void setSize(float x, float y);
        bool nextToPlayer(PlayerActor &player);
        
    private:
};

#endif