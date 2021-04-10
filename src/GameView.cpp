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
  inputManager(*App);
  }

void GameView::setup(){



}

void GameView::update(sf::Event Event){
  sf::Texture texture;
  sf::Texture texture_player;

  string test_level = "../data/bedroom_level_V2.png";
  string player_file = "../data/protag_V1.png";


  if(!texture.loadFromFile(test_level)){
    printf("incorrect file format");
  }

  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }

  sf::Sprite sprite;
  sf::Sprite sprite_player;

  this->App->clear();

  sprite.setTexture(texture);
  this->App->draw(sprite);

  sprite_player.setTexture(texture_player);
  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

  this->App->draw(sprite_player);

  inputManager.update(Event);


}
