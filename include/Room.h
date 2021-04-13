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

        void setUpRoom();

        float myBoundaries[4];
        float myObjects[4];


};

#endif /* MY_CLASS_H */
