#include <iostream>
#include <fstream>
#include "LevelManager.h"

using namespace std;

LevelManager::LevelManager(sf::Texture& levelTexture){
  this->levelTexture = &levelTexture;
}

//read in the level mapping data and store into assoctiative mapping
void LevelManager::init(){
    getRoomNames("../data/RoomNames.txt");

    for(int i = 0; i < myRooms.size(); i++){
    	std::cout << myRooms.at(i) << endl;
    }

    

}

//loads in all the names of the rooms used into myRooms
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

}

// const sf::Texture LevelManager::getLevelTexture(){

// }