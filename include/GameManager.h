#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include "State.h"

class GameManager
{
private:
	sf::RenderWindow *window;
	sf::Event event;

<<<<<<< HEAD:include/Game.h
  	sf::Clock clock;
	float dt;

  	GameView gameView;
=======
	sf::Clock clock;
	float dt;
	std::stack<State*> stateStack;
>>>>>>> adding_game_states:include/GameManager.h

public:
	GameManager();
	//virtual ~Game();

<<<<<<< HEAD:include/Game.h
  	void shutdownGame();


  	void initWindow();
  	void initVariables();
  	void initGameView();
=======
	void shutdownGame();


	void initWindow();
	void initVariables();
	void initStates();
>>>>>>> adding_game_states:include/GameManager.h

	//Update
	void updateDt();
	void update();

	//Render
	void render();

	//Core
	void runGame();
};

#endif
