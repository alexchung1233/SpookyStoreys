#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "GameView.h"

class Game
{
private:
	sf::RenderWindow *window;
	sf::Event event;

  	sf::Clock clock;
	float dt;

  	GameView gameView;

public:
	Game();
	//virtual ~Game();

  	void shutdownGame();


  	void initWindow();
  	void initVariables();
  	void initGameView();

	//Update
	void updateDt();
	void update();

	//Render
	void render();

	//Core
	void runGame();
};

#endif
