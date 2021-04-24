#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>


class LevelManager {

private:
	sf::Texture* levelTexture;
	std::map<std::string, std::string> levelFileMapping;
	std::vector<std::string> myRooms;

	void getRoomNames(std::string roomNamesFilepath);

public:
	LevelManager() { };

	LevelManager(sf::Texture& levelTexture);
	void init();
	void setRoom(std::string roomName);
	//void changeLevelTexture(std::string textureName);
	const sf::Texture getLevelTexture();



};

#endif
