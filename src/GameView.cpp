#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "InputManager.h"

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

  string player_file = "../data/protag_V1.png";

  if(!texture_player.loadFromFile(player_file)){
    printf("incorrect file format");
  }

  sprite.setTexture(texture);
  sprite_player.setTexture(texture_player);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  //sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));
  this->status = State::RUNNING;

}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  inputManager.update(Event, dt);

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

  //test script
  fadeIn();
}

void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(sprite);
    this->App->draw(sprite_player);
    this->App->draw(transitionRectangle);
}

void GameView::pause(){}

void GameView::unpause(){}

void GameView::fadeIn(){
  transitionRectangle.setFillColor(sf::Color(0, 0, 0, transitionRectangleAlphaChannel));

  float timer = clockFilter.getElapsedTime().asSeconds();

  if (timer > 0.08f && transitionRectangleAlphaChannel > 0.f)
  {
          clockFilter.restart();
          transitionRectangleAlphaChannel -= 5;

  }


}
