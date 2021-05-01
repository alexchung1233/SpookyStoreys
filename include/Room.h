#ifndef ROOM_H // include guard
#define ROOM_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Door.h"
#include "HolyWater.h"
#include "Note.h"
#include "Bookcase.h"
#include "Safe.h"
#include "Bathtub.h"

class Room
{

    public:
        Room();
        Room(std::string roomName);

        //set up a room given a file / file path
        void setUpRoom(std::string filepath);
        sf::IntRect getBoundaries();
        std::vector<sf::IntRect> getObstacles();
        sf::Texture getTexture();
        std::vector<Door> getDoors();
        std::vector<ItemActor*> getItems();
        void destroyItem(float idx);

    private:
    	sf::Texture levelTexture;

        sf::IntRect myBoundaries;
        std::vector<sf::IntRect> myObstacles;
        std::vector<Door> myDoors;
        std::vector<ItemActor*> myItems;



};

#endif /* MY_CLASS_H */
