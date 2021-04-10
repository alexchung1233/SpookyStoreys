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



}

void GameView::update(sf::Event Event){
  //sf::Texture texture;
  string test_level = "../data/bedroom_level_V2.png";
  if(!texture.loadFromFile(test_level)){
    printf("incorrect file format");
  }
  //sf::Sprite sprite;
  sprite.setTexture(texture);
  float spriteX = logic->getPlayer().getPosition().x;
  float spriteY = logic->getPlayer().getPosition().y;
  //sprite.setPosition(spriteX, spriteY);
  //sprite.setPosition(0, 0);

  App->draw(sprite);
  inputManager.update(Event);


}
