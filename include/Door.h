#ifndef DOOR_H // include guard
#define DOOR_H
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Position.h"


class Door {
   public:
   		Door(vector<string> inputVector);

	private:
		sf::IntRect doorBoundaries;
		std::string nextRoom;
		Position newPosition;
};

#endif /* MY_CLASS_H */