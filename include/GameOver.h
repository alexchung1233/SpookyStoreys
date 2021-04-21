#ifndef TITLE_GAME_OVER_H // include guard
#define TITLE_GAME_OVER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"

class GameOver : public State
{
	public:
		GameOver();
		GameOver(sf::RenderWindow& app);
		GameOver(sf::RenderWindow& app, std::string myMessage);

		void init();

	  	void update(sf::Event& Event, float dt);
		void render();

		void pause();

	  	void unpause();

	private:
		void makeText(sf::Text& text, std::string string, float yPos);

		sf::Font endFont;

		sf::Text mainMessage;
		sf::Text replayMessage, menuMessage, exitMessage;

};

#endif /* MY_CLASS_H */