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
  inputManager(*App, myLogic);

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
  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

  const sf::Vector2f spriteSize(
    sprite_player.getTexture()->getSize().x * sprite_player.getScale().x,
    sprite_player.getTexture()->getSize().y * sprite_player.getScale().y);

  inputManager.logic.getPlayer().setSize(spriteSize);

  PlayerActor player = inputManager.logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);


}


void GameView::update(sf::Event& Event, float dt){
  this->App->clear();
  inputManager.update(Event, dt);
  //myPos();

  PlayerActor player = inputManager.logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->App->draw(sprite);

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // sf::RectangleShape rectangle(sf::Vector2f(160,100));
  // rectangle.setPosition(sf::Vector2f(160, 350));
  // rectangle.setOutlineThickness(3);
  // rectangle.setOutlineColor(sf::Color(250, 150, 100));
  // rectangle.setFillColor(sf::Color::Transparent);
  // this->App->draw(rectangle);

  this->App->draw(sprite_player);

}

float GameView::myPos(){
  std::cout << "my pos: ";
  std::cout << inputManager.logic.getPlayer().getPosition().x;
  std::cout << ", ";
  std::cout << inputManager.logic.getPlayer().getPosition().y;
  std::cout << "\n";

}

void GameView::setLogic(GameView& logic){}
