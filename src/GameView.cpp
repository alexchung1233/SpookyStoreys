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
  string player_file = "../data/protag_V1.png";

  if(!texture.loadFromFile(test_level)){
    printf("incorrect file format");
  }


  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }
  sprite.setPosition(logic->getPlayer().getPosition().x,
  logic->getPlayer().getPosition().y);
  sprite.setTexture(texture);
  sprite_player.setTexture(texture_player);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

}



void GameView::update(sf::Event Event){
  this->App->clear();
  while(App->pollEvent(Event))
  {
    // Exit
    if(Event.type == sf::Event::Closed) {
      App->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
      App->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      sprite_player.setPosition(sprite_player.getPosition().x
      , sprite_player.getPosition().y-9.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      sprite_player.setPosition(sprite_player.getPosition().x
      , sprite_player.getPosition().y+9.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      sprite_player.setPosition(sprite_player.getPosition().x-9.f
      , sprite_player.getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      sprite_player.setPosition(sprite_player.getPosition().x+9.f
      , sprite_player.getPosition().y);
    }
  }

  this->App->draw(sprite);

  this->App->draw(sprite_player);



}
