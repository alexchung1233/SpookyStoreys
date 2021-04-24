#ifndef ROOM_H // include guard
#define ROOM_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


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

    private:
    	//std::string roomName;
    	sf::Texture levelTexture;

        sf::IntRect myBoundaries;
        std::vector<sf::IntRect> myObstacles;
        std::vector<std::string> myDoor;


};

#endif /* MY_CLASS_H */
