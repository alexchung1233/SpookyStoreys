#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

using namespace std;


//constructor takes in App
GameView::GameView(sf::RenderWindow &app){
  this->App = &app;
  menu temp(app);
  myMenu = temp;
}

void GameView::setup(){
  sf::Texture texture;
  string test_level = "../data/bedroom_level.png";
  if(!texture.loadFromFile(test_level)){
    printf("incorrect file format");
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);
  App->draw(sprite);
}

void GameView::update(sf::Event event){
  myMenu.update(event);
}