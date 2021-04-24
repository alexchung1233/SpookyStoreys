#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "InputManager.h"
#include "Animation.h"

using namespace std;


GameView::GameView(){
  //TODO make this extend off a Process class.
  GameLogic myLogic;
  this->logic = myLogic;
  this->status = State::UNINIT;

}
//constructor takes in App
GameView::GameView(sf::RenderWindow& app){
  //TODO make this extend off a Process class.
  this->App = &app;
  GameLogic myLogic;
  this->logic = myLogic;
  inputManager(*App, logic);
  this->status = State::UNINIT;

}

void GameView::init(){
  //TODO data driven approach so objects aren't hard coded in

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

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  string animate_sprite_file = "../data/example_sprite.png";

  if(!texture_animated.loadFromFile(animate_sprite_file)){
    printf("incorrect file format");
  }

  sprite_animate_example.setPosition(sf::Vector2f(500.f, 300.f));

  animation = Animation(texture_animated, sprite_animate_example);
  

  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));
  this->status = State::RUNNING;
}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  inputManager.update(Event, dt);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
  this->animation.play(dt);
  updatePlayerAnimation();
  this->logic.update(dt);
  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!");
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...");
  }

}


//temporary function to update direction of player
//TODO: make it so it draws from a sprite sheet
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

void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(sprite);

    this->App->draw(sprite_player);
    this->App->draw(sprite_animate_example);

}

void GameView::pause(){}

void GameView::unpause(){}
