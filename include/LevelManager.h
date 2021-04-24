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
	std::string currentLevelName;


public:
	LevelManager() { };

	LevelManager(sf::Texture& levelTexture);
	void init();
	void setRoom(std::string roomName);
	Room getCurrentRoom();
	void getRoomNames(std::string roomNamesFilepath);

	//void changeLevelTexture(std::string textureName);
	const sf::Texture getLevelTexture();



};

#endif