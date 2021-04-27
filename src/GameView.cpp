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
  this->status = State::UNINIT;
}

//constructor takes in App
GameView::GameView(sf::RenderWindow& app){
  //TODO make this extend off a Process class.
  this->App = &app;
  this->status = State::UNINIT;

}

void GameView::init(){
  this->levelManager.init();
  this->logic.setup();
  this->logic.setLevelManager(levelManager);

  inputManager(*App, logic);

  texture = this->levelManager.getLevelTexture();



  levelSprite.setTexture(texture);


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

  texture = this->levelManager.getLevelTexture();
  levelSprite.setTexture(texture);

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

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // sf::RectangleShape rectangle(sf::Vector2f(540,385));
  // rectangle.setPosition(sf::Vector2f(170,175));
  // rectangle.setOutlineThickness(-3);
  // rectangle.setOutlineColor(sf::Color(250, 150, 100));
  // rectangle.setFillColor(sf::Color::Transparent);
  // this->App->draw(rectangle);

}


//temporary function to update direction of player
void GameView::updatePlayerAnimation(float dt){
  PlayerActor player = this->logic.getPlayer();
  switch(player.getMovementState()){


    case MovementStates::IDLE:
      this->player_anim_down.play(gameClock);

      break;

    case MovementStates::MOVING_LEFT:
      this->player_anim_left.play(gameClock);
      break;

    case MovementStates::MOVING_RIGHT:
      this->player_anim_right.play(gameClock);
      break;


    case MovementStates::MOVING_UP:
      this->player_anim_up.play(gameClock);
      break;

    case MovementStates::MOVING_DOWN:
      this->player_anim_down.play(gameClock);
      break;

      }
}

void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(levelSprite);
    this->App->draw(sprite_player);

}

void GameView::pause(){}

void GameView::unpause(){}
