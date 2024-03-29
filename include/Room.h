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
#include "Painting.h"
#include "Firepoker.h"

class Room
{

    public:
        Room();
        Room(std::string roomName);
        Room(std::string roomName, int diff);

        //set up a room given a file / file path
        void setUpRoom(std::string filepath);
        sf::IntRect getBoundaries();
        std::vector<sf::IntRect> getObstacles();
        sf::Texture getTexture();
        std::vector<Door> getDoors();
        std::string getRoomTitle();
        std::vector<ItemActor*> getItems();

    private:
    	std::string roomTitle;
    	sf::Texture levelTexture;

        sf::IntRect myBoundaries;
        std::vector<sf::IntRect> myObstacles;
        std::vector<Door> myDoors;
        std::vector<ItemActor*> myItems;

        int difficultyLevel = 1;

};

#endif /* MY_CLASS_H */
