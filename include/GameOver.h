#ifndef TITLE_GAME_OVER_H // include guard
#define TITLE_GAME_OVER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"

class GameOver : public State
{
public:
	GameOver();

  	void update(sf::Event& Event, float dt);
	void render();

	void pause();

  	void unpause();
};

#endif /* MY_CLASS_H */