#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "InputManager.h"

using namespace std;

//constructor takes in App
void GameView::setup(sf::RenderWindow& app){
  this->App = &app;
  GameLogic myLogic;
  this->logic = myLogic;

  inputManager(*App, logic);

  string test_level = "../data/bedroom_level_V2.png";

  if(!texture.loadFromFile(test_level)){
    printf("incorrect file format");
  }

  string player_file = "../data/protag_V1.png";

  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }

  sprite.setTexture(texture);
  sprite_player.setTexture(texture_player);

  PlayerActor player = inputManager.logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  //sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

}



void GameView::update(sf::Event& Event, float dt){
  this->App->clear();

  inputManager.update(Event, dt);

  PlayerActor player = inputManager.logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->App->draw(sprite);

  this->App->draw(sprite_player);
}

void GameView::updateMenu(sf::Event& Event){
  inputManager.updateMenu(Event);
  drawMenu();
}


void GameView::drawMenu(){
  this->App->clear();

  Menu& menu = inputManager.getMenu();

  this->App->draw(menu.getTitle());
  for(int i = 0; i < 3; i++){
    this->App->draw(menu.getBox(i));
    this->App->draw(menu.getText(i));
  }

}

InputManager& GameView::getManager(){
  return inputManager;
}


float GameView::myPos(){
  std::cout << "my pos: ";
  std::cout << inputManager.logic.getPlayer().getPosition().x;
  std::cout << "\n";

}
