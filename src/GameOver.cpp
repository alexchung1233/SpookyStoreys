#include "GameOver.h"
#include "GameView.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

GameOver::GameOver(){
	this->status = State::UNINIT;


}

GameOver::GameOver(sf::RenderWindow& app, Sound* newSound){
	this->App = &app;
 	this->status = State::UNINIT;
	sound = newSound;
}

GameOver::GameOver(sf::RenderWindow& app, std::string myMessage, Sound* newSound){
	this->App = &app;
 	this->status = State::UNINIT;
 	mainMessage.setString(myMessage);
	sound = newSound;
}

void GameOver::init(){
	this->status = RUNNING;

	if(!endFont.loadFromFile("../data/courier.ttf"))
    	std::cout << "Font unable to load\n";
    mainMessage.setFont(endFont);
	mainMessage.setCharacterSize(80);
	mainMessage.setFillColor(sf::Color(200, 0, 0));

	sf::FloatRect textBounds = mainMessage.getGlobalBounds();

	mainMessage.setPosition(sf::Vector2f(400 - textBounds.width/2, 100));

	replayMessage.setFont(endFont);
	menuMessage.setFont(endFont);
	exitMessage.setFont(endFont);


	makeText(replayMessage, "Hit R to play again", 300);
	makeText(menuMessage, "Hit M for the main menu", 350);
	makeText(exitMessage, "Hit ESC to exit", 400);

//	sound->playPlayingMusic();

}

void GameOver::makeText(sf::Text& text, std::string string, float yPos){
	text.setString(string);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color(255, 255, 255));

	sf::FloatRect textBounds = text.getGlobalBounds();

	text.setPosition(sf::Vector2f(400 - textBounds.width/2, yPos));
}


void GameOver::update(sf::Event& Event, float dt){

	while(App->pollEvent(Event))
	{
	    // Exit
	    if(Event.type == sf::Event::Closed) {
	    	App->close();
	    }
	    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	    {
	    	App->close();
	    }
	    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	    {
				//sound->stopPlayingMusic();
	    	this->status = State::SUCCESS;
			this->childState = new GameView(*App, sound);
	    }
	    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	    {
				sound->stopPlayingMusic();
	    	this->status = State::SUCCESS;
			this->childState = new Menu(*App, sound);
	    }

    }

}

void GameOver::render(){
	this->App->clear();
	this->App->draw(mainMessage);
	this->App->draw(replayMessage);
	this->App->draw(menuMessage);
	this->App->draw(exitMessage);
}

void GameOver::pause(){

}

void GameOver::unpause(){

}