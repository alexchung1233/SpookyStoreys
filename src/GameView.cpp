#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "InputManager.h"

using namespace std;

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
  
  PlayerActor player = inputManager.logic->getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  //sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));
  this->status = State::RUNNING;

}



// void GameView::update(sf::Event& Event, float dt){
//   this->App->clear();

//   inputManager.update(Event, dt);

//   PlayerActor player = inputManager.logic.getPlayer();
//   sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

//   this->App->draw(sprite);

//   this->App->draw(sprite_player);
// }

// void GameView::updateMenu(sf::Event& Event){
//   inputManager.updateMenu(Event);
//   drawMenu();
// }


//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  inputManager.update(Event, dt);

  PlayerActor player = inputManager.logic->getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
}
//>>>>>>> adding_game_states

// void GameView::drawMenu(){
//   this->App->clear();

//   Menu& menu = inputManager.getMenu();

//   this->App->draw(menu.getTitle());
//   for(int i = 0; i < 3; i++){
//     this->App->draw(menu.getBox(i));
//     this->App->draw(menu.getText(i));
//   }
// }

// InputManager& GameView::getManager(){
//   return inputManager;
// }

//<<<<<<< HEAD
//=======
void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(sprite);
    this->App->draw(sprite_player);
}

void GameView::pause(){}

void GameView::unpause(){}
