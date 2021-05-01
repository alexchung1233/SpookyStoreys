#include "GameView.h"
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

  string counter_file = "../data/counter.png";
  if(!texture_counter.loadFromFile(counter_file)){
    printf("incorrect file format");
  }
  sprite_counter.setTexture(texture_counter);
  sprite_counter.setPosition(732, 0);


  setCounterText();

  //sprite_player.setScale(sf::Vector2f(0.80f, 0.80f));


  makeBox(sf::Vector2f(logic.dialoguebox.position.x, logic.dialoguebox.position.y), sf::Color::Black);

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

void GameView::setCounterText(){
  if (!font.loadFromFile("../data/courier.ttf")){
      std::cout << "incorrect font";
  }
  this->counterText.setString("0");
  this->counterText.setCharacterSize(50);
  this->counterText.setFillColor(sf::Color::White);
  this->counterText.setFont(font);
  this->counterText.setPosition(sf::Vector2f(752, 62));
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
  this->counterText.setString(to_string(player.getHolyWaterCount()));

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
  // int size = levelManager.getCurrentRoom().getObstacles().size();
  // for(int i = 0; i < size; i++){
  //   sf::IntRect checkMe = levelManager.getCurrentRoom().getObstacles().at(i);
  //   sf::RectangleShape rectangle(sf::Vector2f(checkMe.width,checkMe.height));
  //   rectangle.setPosition(sf::Vector2f(checkMe.left,checkMe.top));
  //   rectangle.setOutlineThickness(-3);
  //   rectangle.setOutlineColor(sf::Color(250, 150, 100));
  //   rectangle.setFillColor(sf::Color::Transparent);
  //   this->App->draw(rectangle);
  // }


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
    this->App->draw(sprite_counter);
    this->App->draw(counterText);
    isDialogue();

}


void GameView::isDialogue(){
  if (logic.isDialogueBoxUsed()){ //toggle the dialogue box, if the  player has some sort of interaction
    this->App->draw(dialogueBox);
    this->App->draw(message);
  }
}

//creat the box and position of box
void GameView::makeBox(sf::Vector2f position, sf::Color color){
    this->dialogueBox.setFillColor(color);
    this->dialogueBox.setSize(sf::Vector2f(790, 40));
    this->dialogueBox.setOutlineColor(sf::Color::White);
    this->dialogueBox.setOutlineThickness(2);

    sf::Vector2f myPos = sf::Vector2f(position.x - this->dialogueBox.getSize().x/2, 550);

    dialogueBox.setPosition(myPos);
}

//set the text for the dialoguebox
void GameView::setText(std::string words){
  this->message.setString(words);
  this->message.setCharacterSize(15);
  this->message.setFillColor(sf::Color::Red);
  this->message.setFont(font);

  sf::FloatRect boxBounds = this->dialogueBox.getGlobalBounds();
  sf::FloatRect textBounds = this->message.getLocalBounds();

  sf::Vector2f myPos = sf::Vector2f(boxBounds.left + boxBounds.width/2 - textBounds.width/2,
    boxBounds.top + boxBounds.height/2.7 - textBounds.height/2);

  this->message.setPosition(myPos);

}





void GameView::pause(){}

void GameView::unpause(){}
