#include "Door.h"

using namespace std;

Door::Door(vector<string> inputVector){
    this->doorBoundaries.left = stoi(inputVector.at(0));
    this->doorBoundaries.top = stoi(inputVector.at(1));
    this->doorBoundaries.width = stoi(inputVector.at(2));
    this->doorBoundaries.height = stoi(inputVector.at(3));

    this->nextRoom = inputVector.at(4);

    this->newPosition = Position(stoi(inputVector.at(5)), stoi(inputVector.at(6)));
}

sf::IntRect Door::getDoorBoundaries(){
    return this->doorBoundaries;
}

string Door::getNextRoom(){
    return this->nextRoom
}

Position Door::getNewPosition(){
    return this->newPosition
}