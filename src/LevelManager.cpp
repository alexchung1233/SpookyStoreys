//handles the transition and loading of levels. Carries an Room object
#include <iostream>
#include <fstream>
#include "LevelManager.h"

using namespace std;

//read in the level mapping data and store into assoctiative mapping
void LevelManager::init(int difficultyLevel){

    getRoomNames("../data/RoomNames.txt");

    for(int i = 0; i < myRooms.size(); i++){
    	levelFileMapping[myRooms.at(i)] = Room(myRooms.at(i), difficultyLevel);
    }

    currentLevelName = myRooms.at(0);

    idxItemToDestroy = -1;

}

//helper function that loads in all the names of the rooms used into myRooms
void LevelManager::getRoomNames(std::string roomNamesFilepath){
    std::string str;
    ifstream infile;
	infile.open (roomNamesFilepath);
    while(!infile.eof())
    {
    	std::getline(infile, str);
    	myRooms.push_back(str);
    }
    infile.close();
}

void LevelManager::setRoom(std::string roomName){
	currentLevelName = roomName;
}

Room LevelManager::getCurrentRoom(){
	return levelFileMapping[currentLevelName];
}

const sf::Texture LevelManager::getLevelTexture(){
	return levelFileMapping[currentLevelName].getTexture();
}
