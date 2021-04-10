#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "InputManager.h"

using namespace std;



//constructor takes in App
GameView::GameView(sf::RenderWindow& app){
  this->App = &app;
  inputManager(*App, *logic);
  }

void GameView::setup(){
  string test_level = "../data/bedroom_level_V2.png";

  if(!texture.loadFromFile(test_level)){
    printf("incorrect file format");
  }

  sprite.setPosition(logic->getPlayer().getPosition().x,
  logic->getPlayer().getPosition().y);
  sprite.setTexture(texture);

}



void GameView::update(sf::Event Event){

  App->clear();

  inputManager.update(Event);

  this->App->draw(sprite);






}
