#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "InputManager.h"
#include "Animation.h"

using namespace std;



//constructor takes in App
GameView::GameView(sf::RenderWindow& app){
  this->App = &app;
  GameLogic myLogic;
  this->logic = myLogic;

  inputManager(*App, logic);

}

void GameView::setup(){

  string test_level = "../data/bedroom_level_V2.png";

  if(!texture.loadFromFile(test_level)){
    printf("incorrect file format");
  }

  string player_file = "../data/protag_V1.png";

  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }

  sprite.setTexture(texture);

  PlayerActor player = inputManager.logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  //sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

  //animation = Animation(texture_player, sprite_player);
  //sprite_player.setTexture(texture_player);

}



void GameView::update(sf::Event& Event, float dt){
  this->App->clear();
  inputManager.update(Event, dt);

  //fix this so it doesn't use input maager anymore
  PlayerActor player = inputManager.logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->App->draw(sprite);

  //this->animation.play(dt);
  updatePlayerAnimation();

  this->App->draw(sprite_player);



}

void GameView::updatePlayerAnimation(){
  PlayerActor player = inputManager.logic.getPlayer();
  switch(player.getMovementState()){
    case MovementStates::IDLE:
      sprite_player.setTexture(texture_player);
      break;
  }


}

float GameView::myPos(){
  std::cout << "my pos: ";
  std::cout << inputManager.logic.getPlayer().getPosition().x;
  std::cout << "\n";

}
