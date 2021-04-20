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

GameOver::GameOver(sf::RenderWindow& app){
	this->App = &app;
 	this->status = State::UNINIT;
}

GameOver::GameOver(sf::RenderWindow& app, std::string myMessage){
	this->App = &app;
 	this->status = State::UNINIT;
 	mainMessage.setString(myMessage);
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

	commandMessage.setFont(endFont);
	commandMessage.setString("Hit R to play again\nHit M for main menu\nHit ESC to exit");
	commandMessage.setCharacterSize(40);
	commandMessage.setFillColor(sf::Color(255, 255, 255));

	textBounds = commandMessage.getGlobalBounds();

	commandMessage.setPosition(sf::Vector2f(400 - textBounds.width/2, 300));	

}

void GameOver::setMessage(std::string myText){
	mainMessage.setString(myText);
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
	    	this->status = State::SUCCESS;
			childState = new GameView(*App);
	    }
	    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	    {
	    	this->status = State::SUCCESS;
			childState = new Menu(*App);
	    }

    }

}

void GameOver::render(){
	this->App->clear();
	this->App->draw(mainMessage);
	this->App->draw(commandMessage);

}

void GameOver::pause(){

}

void GameOver::unpause(){

}