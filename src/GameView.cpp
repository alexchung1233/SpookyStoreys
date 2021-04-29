#include "GameView.h"
#include <string>
#include <iostream>

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

  string player_file = "../data/protag_V1.png";

  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }

  levelSprite.setTexture(texture);
  sprite_player.setTexture(texture_player);
  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->status = State::RUNNING;

}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  inputManager.update(Event, dt);

  texture = this->levelManager.getLevelTexture();
  levelSprite.setTexture(texture);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!");
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...");
  }

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // sf::RectangleShape rectangle(sf::Vector2f(650,380));
  // rectangle.setPosition(sf::Vector2f(75,170));
  // rectangle.setOutlineThickness(-3);
  // rectangle.setOutlineColor(sf::Color(250, 150, 100));
  // rectangle.setFillColor(sf::Color::Transparent);
  // this->App->draw(rectangle);

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
