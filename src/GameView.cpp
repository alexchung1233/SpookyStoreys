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


  sprite.setTexture(texture);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  string animate_sprite_file = "../data/Protag_Spritesheet.png";

  if(!player_sprite_sheet.loadFromFile(animate_sprite_file)){
    printf("incorrect file format");
  }


  player_anim_down = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 0);
  player_anim_up = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 107);
  player_anim_left = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 214);
  player_anim_right = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 321);


  this->status = State::RUNNING;
}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  inputManager.update(Event, dt);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
  updatePlayerAnimation(dt);
  //this->logic.update(dt);

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
void GameView::updatePlayerAnimation(float dt){
  PlayerActor player = this->logic.getPlayer();
  switch(player.getMovementState()){


    case MovementStates::IDLE:
      this->player_anim_down.play(dt);

      break;

    case MovementStates::MOVING_LEFT:
      this->player_anim_left.play(dt);
      break;

    case MovementStates::MOVING_RIGHT:
      this->player_anim_right.play(dt);
      break;


    case MovementStates::MOVING_UP:
      this->player_anim_up.play(dt);
      break;

    case MovementStates::MOVING_DOWN:
      this->player_anim_down.play(dt);
      break;

      }
}

void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(sprite);

    this->App->draw(sprite_player);

}

void GameView::pause(){}

void GameView::unpause(){}
