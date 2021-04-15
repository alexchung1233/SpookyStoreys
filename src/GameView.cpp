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


}

void GameView::setup(){

  inputManager(*App, logic);

  string test_level = "../data/bedroom_level_V2.png";

  if(!texture.loadFromFile(test_level)){
    printf("incorrect file format");
  }

  string player_file = "../data/protag_front.png";

  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }


  sprite.setTexture(texture);

  PlayerActor player = logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  //sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

  string animate_sprite_file = "../data/example_sprite.png";

  if(!texture_animated.loadFromFile(animate_sprite_file)){
    printf("incorrect file format");
  }

  sprite_animate_example.setPosition(sf::Vector2f(500.f, 300.f));

  animation = Animation(texture_animated, sprite_animate_example);
  //sprite_player.setTexture(texture_player);

}


void GameView::update(sf::Event& Event, float dt){
  this->App->clear();
  inputManager.update(Event, dt);
  PlayerActor player = logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->App->draw(sprite);

  this->animation.play(dt);
  updatePlayerAnimation();

  this->App->draw(sprite_player);
  this->App->draw(sprite_animate_example);


  this->logic.update(dt);






}

void GameView::updatePlayerAnimation(){
  PlayerActor player = this->logic.getPlayer();
  switch(player.getMovementState()){
    case MovementStates::IDLE:
      sprite_player.setTexture(texture_player);
      break;
    case MovementStates::MOVING_LEFT:
      if(!texture_player.loadFromFile("../data/protag_left_side.png")){
        printf("incorrect file format");
      }
      sprite_player.setTexture(texture_player);
      break;
    case MovementStates::MOVING_RIGHT:
      if(!texture_player.loadFromFile("../data/protag_right_side.png")){
        printf("incorrect file format");
      }
      sprite_player.setTexture(texture_player);
      break;
    case MovementStates::MOVING_UP:
      if(!texture_player.loadFromFile("../data/protag_behind.png")){
        printf("incorrect file format");
      }
      sprite_player.setTexture(texture_player);
      break;
    case MovementStates::MOVING_DOWN:
        if(!texture_player.loadFromFile("../data/protag_front.png")){
          printf("incorrect file format");
        }
        sprite_player.setTexture(texture_player);
        break;
  }


}

float GameView::myPos(){
  std::cout << "my pos: ";
  //std::cout << inputManager.logic.getPlayer().getPosition().x;
  std::cout << "\n";

}

void GameView::setLogic(GameView& logic){}
