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
  this->audioManager = &audioManager;
  this->status = State::UNINIT;

}

void GameView::init(){
  this->levelManager.init();
  this->logic.setup();
  this->logic.setLevelManager(levelManager);
  this->scriptManager.readInScript("test_script");
  this->transitionRectangleAlphaChannel = 255;

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
  this->dt = dt;
  inputManager.update(Event, dt);

  texture = this->levelManager.getLevelTexture();
  levelSprite.setTexture(texture);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
  updatePlayerAnimation(dt);

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

  if(inputManager.getPlayState() == 1){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Win!", *audioManager);
  }
  else if(inputManager.getPlayState() == 2){
    this->status = State::SUCCESS;
    childState = new GameOver(*App, "You Lose...", *audioManager);
  }



  //run test script
  executeScript();

  //test script
  //fadeIn(16.f, 0, 0, 0);

  //THIS CODE IS TO SEARCH FOR HITBOXES, DON'T DELETE UNTIL WE TURN IN
  // sf::RectangleShape rectangle(sf::Vector2f(540,385));
  // rectangle.setPosition(sf::Vector2f(170,175));
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
    //this->App->draw(sprite_monster);
    this->App->draw(transitionRectangle);

}

void GameView::pause(){}

void GameView::unpause(){}

//create function to initalize command
//create states for each command to indicate if finished or not

void GameView::executeScript(){

    ScriptCommand* currentCommand = this->scriptManager.scriptQueue.front();

    if(!this->scriptManager.scriptQueue.empty()){
      //if uninitalized, initalize

      //if finished, pop off

      if(currentCommand->getStatus() == ScriptCommand::UNINIT){
        this->initScriptCommand(*currentCommand);
        currentCommand->setStatus(ScriptCommand::RUNNING);
      }
      else if(currentCommand->getStatus() == ScriptCommand::RUNNING){
        this->updateScriptCommand(*currentCommand);
      }

      else if(currentCommand->getStatus() == ScriptCommand::SUCCESS){
        this->scriptManager.scriptQueue.pop();
      }



    }

}


//initalizes the script command based on a base data
void GameView::initScriptCommand(ScriptCommand& command){
  vector<string> data = command.getData();

  switch(command.getCommandType()){

    case ScriptCommand::FADE_IN:
      command.setStatus(ScriptCommand::RUNNING);
      break;

    case ScriptCommand::WAIT:
      clockFilter.restart();
      break;

    case ScriptCommand::PLAY_SOUND:
      audioManager->setGeneralBuffer(data.at(1));
      audioManager->playGeneralBuffer();
      break;

    case ScriptCommand::SHOW_DIALOGUE:
      break;


  }


}

void GameView::updateScriptCommand(ScriptCommand& command){
  vector<string> data = command.getData();

  switch(command.getCommandType()){

    //matches the command to the type
    case ScriptCommand::FADE_IN:
      fadeIn(
        stof(data.at(1)),stof(data.at(2)), stof(data.at(3)), stof(data.at(4)));
      //finish condition
      if(transitionRectangleAlphaChannel <= 0){
        command.setStatus(ScriptCommand::SUCCESS);
        transitionRectangleAlphaChannel = 255;
      }
      break;

    //move player up based on distance and delayed timer(how slowly it walks)
    case ScriptCommand::MOVE_PLAYER_UP:
      {
        float timer = clockFilter.getElapsedTime().asSeconds() * 100;

        if (timer > 6.f){
          this->logic.upPressed(this->dt);
          clockFilter.restart();
        }
      }
      break;

    //pauses based on seconds
    case ScriptCommand::WAIT:
      {
        float timer = stof(data.at(1));
        if(timer <= clockFilter.getElapsedTime().asSeconds()){
          clockFilter.restart();
          command.setStatus(ScriptCommand::SUCCESS);
        }
      }
      break;

    case ScriptCommand::PLAY_SOUND:
      if(audioManager->getStatusGeneral() == sf::SoundSource::Status::Stopped)
        command.setStatus(ScriptCommand::SUCCESS);
      break;

    case ScriptCommand::SHOW_DIALOGUE:
      break;



  }
}



//Game Effects

//fades in
void GameView::fadeIn(float duration, int r, int g, int b){
  transitionRectangle.setFillColor(sf::Color(r, g, b, transitionRectangleAlphaChannel));

  float timer = clockFilter.getElapsedTime().asSeconds() * 100;

  if (timer > duration && transitionRectangleAlphaChannel > 0.f)
  {
          clockFilter.restart();
          transitionRectangleAlphaChannel -= 5;

  }

}

//fades out
void GameView::fadeOut(float duration, int r, int g, int b){
  transitionRectangle.setFillColor(sf::Color(r, g, b, transitionRectangleAlphaChannel));

  float timer = clockFilter.getElapsedTime().asSeconds() * 100;

  if (timer > duration && transitionRectangleAlphaChannel < 255.f)
  {
          clockFilter.restart();
          transitionRectangleAlphaChannel += 5;

  }

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
