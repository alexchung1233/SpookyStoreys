#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Room.h"

class LevelManager {

private:
	std::map<const std::string, Room> levelFileMapping;
	std::vector<std::string> myRooms;
	float idxItemToDestroy;

public:
	LevelManager() { };
	std::string currentLevelName;
	LevelManager(sf::Texture& levelTexture);
	void init(int difficultyLevel = 1);
	void setRoom(std::string roomName);
	Room getCurrentRoom();
	void getRoomNames(std::string roomNamesFilepath);


	const sf::Texture getLevelTexture();



};

#endif
