#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <queue>
#include "State.h"

class GameManager
{
private:
	sf::RenderWindow *window;
	sf::Event event;

	sf::Clock clock;
	float dt;
	std::queue<State*> stateQueue;

public:
	GameManager();
	//virtual ~Game();

	void shutdownGame();


	void initWindow();
	void initVariables();
	void initStates();

	//Update
	void updateDt();
	void update();

	//Render
	void render();

	//Core
	void runGame();
};

#endif
