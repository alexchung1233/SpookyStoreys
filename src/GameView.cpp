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
  MonsterView newMonster;
  this->monsterView = newMonster;
  inputManager(*App, logic);
  monsterAI(monsterView);
  this->status = State::UNINIT;
  this->audioManager = &audioManager;
}

void GameView::init(){
  this->levelManager.init();
  this->logic.setup();
  this->logic.setLevelManager(levelManager);

  this->monsterLevelManager.init();
  this->monsterLevelManager.setRoom("BASEMENT");

  this->monsterView.setup();
  this->monsterView.setLevelManager(monsterLevelManager);

  inputManager(*App, logic);
  monsterAI(monsterView);
  sf::Vector2f newDoor = this->monsterView.getRandomDoor();
  monsterAI.setDoorLoc(newDoor.x, newDoor.y);
  monsterView.newDoorX = newDoor.x;
  monsterView.newDoorY = newDoor.y;

  texture = this->levelManager.getLevelTexture();



  levelSprite.setTexture(texture);


  PlayerActor player = this->logic.getPlayer();
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
  MonsterActor monster = this->monsterView.getMonster();
  //monsterAI.setPosition(monster.getPosition().x, monster.getPosition().y);
  sprite_monster.setTexture(texture_monster);
  sprite_monster.setPosition(monster.getPosition().x - 200, monster.getPosition().y - 70);
  sprite_monster.setScale(sf::Vector2f(1.00f, 1.00f));

  //sound->playPlayingMusic();
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


  bool inSameRoom = (monsterLevelManager.getCurrentRoom().getRoomTitle() == levelManager.getCurrentRoom().getRoomTitle());

  monsterAI.calculateMove(player.getPosition().x, player.getPosition().y, dt, levelManager.getCurrentRoom().getRoomTitle(), inSameRoom);
  MonsterActor monster = this->monsterView.getMonster();
  sprite_monster.setPosition(monster.getPosition().x - 60, monster.getPosition().y - 30);

  if (inSameRoom) {
    float distX = pow(monster.getPosition().x - player.getPosition().x, 2);
    float distY = pow(monster.getPosition().y - player.getPosition().y, 2);




    if (sqrt(distX + distY) < 70){
      this->status = State::SUCCESS;
      audioManager->stopNextRoom();
      audioManager->stopInRoom();
      childState = new GameOver(*App, "You Lose...", *audioManager);
    }





    //monsterView.sendToBasement();



  }
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

void GameView::setLogic(GameView& logic){}

//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(levelSprite);
    this->App->draw(sprite_player);


    //If the monster is in the same room a the player
    if (monsterLevelManager.getCurrentRoom().getRoomTitle() == levelManager.getCurrentRoom().getRoomTitle()) {
      //If the in room sound isnt already playing
      if (!inRoomLastTime){
        audioManager->playInRoom();
      }
      //Draw monster
      inRoomLastTime = true;
      this->App->draw(sprite_monster);
    }
    else {
      //If they aren't in the same room stop in room sound
      inRoomLastTime = false;
      audioManager->stopInRoom();
    }

    //Get title of current monster room and list of doors from player room
    string monsterRoom = monsterLevelManager.getCurrentRoom().getRoomTitle();
    std::vector<Door> doorList = levelManager.getCurrentRoom().getDoors();
    bool inNextRoom = false;
    bool holdLastTime;
    //Iterate through list of player doors
    for (int i = 0; i < doorList.size(); i++) {
      //If they are equal mark as true
      if (doorList.at(i).getNextRoom() == monsterRoom) {
        inNextRoom = true;
        holdLastTime = true;
      }
    }
    //If the monster is in the next room and sound isnt already playing, play next room sound
    if (inNextRoom) {
      if (!nextRoomLastTime){
        audioManager->playNextRoom();
      }
    }
    //Else stop playing next room sound
    else {
      holdLastTime = false;
      audioManager->stopNextRoom();
    }

    nextRoomLastTime = holdLastTime;


    /*
    sf::RectangleShape monsterRect = sf::RectangleShape(monsterView.getMonster().getSize());
    monsterRect.setPosition(monsterView.getMonster().getPosition().x, monsterView.getMonster().getPosition().y);
    this->App->draw(monsterRect);

    sf::CircleShape doorCenter = sf::CircleShape(1);
    doorCenter.setPosition(monsterView.newDoorX, monsterView.newDoorY);
    this->App->draw(doorCenter);
    */

}

void GameView::pause(){}

void GameView::unpause(){}
