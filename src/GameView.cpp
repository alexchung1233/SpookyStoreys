#include "GameView.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <math.h>
#include "InputManager.h"
#include "Animation.h"
#include "MonsterAI.h"


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


GameView::GameView(sf::RenderWindow& app, AudioManager& audioManager){
  //TODO make this extend off a Process class.
  this->App = &app;
  GameLogic myLogic;
  this->logic = myLogic;
  inputManager(*App, logic);
  this->status = State::UNINIT;
  this->audioManager = &audioManager;
}

void GameView::init(){
  this->levelManager.init();
  this->logic.setup();
  this->logic.setLevelManager(levelManager);

  inputManager(*App, logic);

  //get current level texture
  texture = this->levelManager.getLevelTexture();



  levelSprite.setTexture(texture);


  PlayerActor player = this->inputManager.logic->getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  string animate_sprite_file = "../data/Protag_Spritesheet.png";

  if(!player_sprite_sheet.loadFromFile(animate_sprite_file)){
    printf("incorrect file format");
  }

  //sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));


  player_anim_down = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 0);
  player_anim_up = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 107);
  player_anim_left = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 214);
  player_anim_right = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 321);

  string monster_file = "../data/Monster.png";
  if(!texture_monster.loadFromFile(monster_file)){
    printf("incorrect file format");
  }

  //MonsterAI monsterAI;
  monsterAI.setPosition(400, 360);
  sprite_monster.setTexture(texture_monster);
  sprite_monster.setPosition(400, 360);
  sprite_monster.setScale(sf::Vector2f(-1.00f, 1.00f));

  //sound->playPlayingMusic();
  this->status = State::RUNNING;

}

//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  itemSprites.clear();
  itemTextures.clear();
  inputManager.update(Event, dt);

  //get the latest level texture
  texture = this->levelManager.getLevelTexture();


  //update the level sprite
  levelSprite.setTexture(texture);

  PlayerActor player = this->inputManager.logic->getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
  updatePlayerAnimation(dt);
  //this->logic.update(dt);

/*

All monster AI stuff

  monsterAI.calculateMove(player.getPosition().x, player.getPosition().y, dt);
  sprite_monster.setPosition(monsterAI.positionX, monsterAI.positionY);


  float distX = pow(monsterAI.positionX - player.getPosition().x-125, 2);
  float distY = pow(monsterAI.positionY - player.getPosition().y+20, 2);


  if (sqrt(distX + distY) < 70){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...", sound);
  }
  */

  loadItemsandDialogueBox();


  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!", *audioManager);
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...", *audioManager);
  }

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // sf::RectangleShape rectangle(sf::Vector2f(540,385));
  // rectangle.setPosition(sf::Vector2f(170,175));
  // rectangle.setOutlineThickness(-3);
  // rectangle.setOutlineColor(sf::Color(250, 150, 100));
  // rectangle.setFillColor(sf::Color::Transparent);
  // this->App->draw(rectangle);
  isDialogue();


}


//temporary function to update direction of player
void GameView::updatePlayerAnimation(float dt){
  PlayerActor player = this->logic.getPlayer();
  switch(player.getMovementState()){

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
    this->logic.setMovementState(MovementStates::IDLE);
}

void GameView::loadItemsandDialogueBox(){
  Room tempRoom = levelManager.getCurrentRoom();

  for(int i = 0; i < tempRoom.getItems().size(); i++) {

    ItemActor* item = tempRoom.getItems().at(i);

    itemTextures.push_back(new sf::Texture);

    if(!itemTextures.back()->loadFromFile(item->getSpriteFile())){
      printf("incorrect file format");
    }

    itemSprites.push_back(new sf::Sprite);

    texture_item = itemTextures.back();
    itemSprites.back()->setTexture(*texture_item);
    itemSprites.back()->setPosition(item->getPosition().x, item->getPosition().y);

    inputManager.logic->setUpDialogueBox(item, dialoguebox, i);
    
  }

  if(!dialoguebox.getUsingState()){
    inputManager.logic->Etracker = 0; //reset Etracker
  }

}

void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(levelSprite);
    
    Room tempRoom = levelManager.getCurrentRoom();
    for (int i = 0; i < tempRoom.getItems().size(); i++){
      sf::Sprite* drawMe = itemSprites.at(i);
      this->App->draw(*drawMe);
    }

    this->App->draw(sprite_player);
    this->App->draw(sprite_monster);

}


void GameView::isDialogue(){
  if (dialoguebox.tracker <= dialoguebox.getDialogueLimit() && dialoguebox.getUsingState()){ //toggle the dialogue box, if the  player has some sort of interaction
    this->App->draw(dialoguebox.dialogueBox);
    this->App->draw(dialoguebox.message);
  }else if (dialoguebox.tracker == 0 && this->inputManager.logic->Etracker != 0){ //for the first interaction with an item of any kind
    this->App->draw(dialoguebox.dialogueBox);
    this->App->draw(dialoguebox.message);
  }else{
    //cout << "N0";
  }

}


void GameView::pause(){}

void GameView::unpause(){}
