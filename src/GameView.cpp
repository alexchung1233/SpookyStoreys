#include "GameView.h"

using namespace std;


GameView::GameView(){
  this->status = State::UNINIT;

}

//constructor takes in App
GameView::GameView(sf::RenderWindow& app){
  this->App = &app;
  this->status = State::UNINIT;
}

GameView::GameView(sf::RenderWindow& app, AudioManager& audioManager, int diff){
  this->App = &app;
  inputManager(*App, logic);
  this->status = State::UNINIT;
  this->audioManager = &audioManager;
  this->difficultyLevel = diff;
  this->status = State::UNINIT;
}

void GameView::init(){
  if (!font.loadFromFile("../data/courier.ttf")){
    std::cout << "incorrect font";
  }
  this->levelManager.init(difficultyLevel);
  this->logic.setLevelManager(levelManager);

  //load in the new game intro level script
  this->scriptManager.readInScript("Intro_Script");
  this->transitionRectangle.setFillColor(sf::Color(0, 0, 0));


  this->monsterLevelManager.init();
  this->monsterLevelManager.setRoom("BASEMENT");
  this->logic.setMonsterLevelManager(monsterLevelManager);

  this->logic.setup();

  inputManager(*App, logic);

  //get current level texture
  texture = this->levelManager.getLevelTexture();

  levelSprite.setTexture(texture);

  PlayerActor player = this->logic.getPlayer();

  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);
  sprite_player.setPosition(sf::Vector2f(400.f, 300.f));
  string animate_sprite_file = "../data/Protag_Spritesheet.png";

  if(!player_sprite_sheet.loadFromFile(animate_sprite_file)){
    printf("incorrect file format");
  }

  loadItemTextures();

  setUpInventoyDisplay();

  makeBox(sf::Vector2f(logic.getDialogueBox().position.x, logic.getDialogueBox().position.y), sf::Color::Black);

  float player_time_limit = .6f;

  player_anim_down = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 0, player_time_limit);
  player_anim_up = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 107, player_time_limit);
  player_anim_left = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 214, player_time_limit);
  player_anim_right = Animation(player_sprite_sheet, sprite_player, 48, 107, 96, 0, 0, 321, player_time_limit);

  string monster_sprite_sheet = "../data/monster_sprite_sheet.png";
  if(!texture_monster.loadFromFile(monster_sprite_sheet)){
    printf("incorrect file format");
  }

  //limit how slow the monster animation should be
  float monster_anim_limit = 10.f;

  this->monster_anim_left = Animation(texture_monster, sprite_monster, 102, 71, 102, 0, 0, 0, monster_anim_limit);
  this->monster_anim_right = Animation(texture_monster, sprite_monster, 102, 71, 102, 0, 0, 71, monster_anim_limit);

  MonsterActor monsterActor = this->logic.getMonsterActor();
  this->sprite_monster.setPosition(monsterActor.getPosition().x - 200, monsterActor.getPosition().y - 70);
  this->sprite_monster.setScale(sf::Vector2f(2.00f, 2.00f));

  this->status = State::RUNNING;

}



//update the running game state depending on logic and input
void GameView::update(sf::Event& Event, float dt){
  this->dt = dt;

  itemSprites.clear();

  inputManager.update(Event, dt);
  logic.updateAI(dt);

  //get the latest level texture
  texture = this->levelManager.getLevelTexture();

  //update the level sprite
  levelSprite.setTexture(texture);

  PlayerActor player = this->logic.getPlayer();
  sprite_player.setPosition(player.getPosition().x, player.getPosition().y);

  this->holyWaterCounter_text.setString(to_string(player.getInventory()->getHolyWaterCount()));
  this->noteCounter_text.setString(to_string(player.getInventory()->numNotesFound()));
  this->keyCounter_text.setString(to_string(player.getInventory()->getKeyCount()));

  updatePlayerAnimation(dt);
  updateMonsterAnimation(dt);

  MonsterActor monster = this->logic.getMonsterActor();
  sprite_monster.setPosition(monster.getPosition().x - 60, monster.getPosition().y - 30);


  loadItemSprites();

  this->setText(logic.getDialogueBoxText());

  //transitions to the next state
  if(logic.getPlayState() == 1){
    this->status = State::SUCCESS;
    audioManager->stopNextRoom();
    audioManager->stopInRoom();
    childState = new GameOver(*App, "You Win!", *audioManager, difficultyLevel);
  }
  else if(logic.getPlayState() == 2){
    this->status = State::SUCCESS;
    audioManager->stopNextRoom();
    audioManager->stopInRoom();
    audioManager->playMonsterScream();
    childState = new GameOver(*App, "You Lose...", *audioManager, difficultyLevel);
  }


  //if player elects not to skip cutscene, then continue
  if(inputManager.getPlayState()!=1){
    executeScript();
  }
  else{
    scriptManager.clearQueue();
    postScript();
  }

}


//renders the running game
void GameView::render(){
    this->App->clear();
    this->App->draw(levelSprite);
    Room tempRoom = levelManager.getCurrentRoom();

    for (int i = 0; i < itemSprites.size(); i++){
      sf::Sprite* drawMe = itemSprites.at(i);
      this->App->draw(*drawMe);
    }

    this->App->draw(sprite_player);


    monsterSpriteAndSounds();

    this->App->draw(sprite_inventoryDisplay);
    this->App->draw(holyWaterCounter_text);
    this->App->draw(noteCounter_text);
    this->App->draw(keyCounter_text);
    this->App->draw(transitionRectangle);

    isDialogue();

}


void GameView::postSuccess(){
  this->logic.postLogic();
  this->App->clear();
}

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
      this->transitionRectangleAlphaChannel = 255;
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
      logic.setDialogueBoxStatus(true);
      logic.setDialogueBoxText(data.at(1));
      break;
    case ScriptCommand::PAUSE_MONSTER:
      logic.pauseMonster();
      break;
    case ScriptCommand::START_MONSTER:
      logic.startMonster();
      break;
    case ScriptCommand::LOCK_PLAYER:
      logic.setPlayerLock(true);
      break;
    case ScriptCommand::UNLOCK_PLAYER:
      logic.setPlayerLock(false);
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
      if(!logic.getDialogueBoxUsingState()){
        command.setStatus(ScriptCommand::SUCCESS);
        }
      break;
    case ScriptCommand::PAUSE_MONSTER:
      if(logic.isMonsterPaused()){
        command.setStatus(ScriptCommand::SUCCESS);
        }
      break;
    case ScriptCommand::START_MONSTER:
      if(!logic.isMonsterPaused()){
        command.setStatus(ScriptCommand::SUCCESS);
        }

      break;

    case ScriptCommand::LOCK_PLAYER:
      if(logic.isPlayerLocked()){
        command.setStatus(ScriptCommand::SUCCESS);
        }

      break;

    case ScriptCommand::UNLOCK_PLAYER:
      if(!logic.isPlayerLocked()){
        command.setStatus(ScriptCommand::SUCCESS);
        }

      break;
  }
}


void GameView::postScript(){
  logic.startMonster();
  logic.setPlayerLock(false);
  this->transitionRectangleAlphaChannel = 0;
  this->transitionRectangle.setFillColor(sf::Color(0, 0, 0, transitionRectangleAlphaChannel));

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

    default:
      //do nothing
     break;
  }
  this->logic.setPlayerMovementState(MovementStates::IDLE);
}


//temporary function to update direction of player
void GameView::updateMonsterAnimation(float dt){
  MonsterActor monster = this->logic.getMonsterActor();
  switch(monster.getMovementState()){
    case MovementStates::MOVING_LEFT:
      this->monster_anim_left.play(dt);
      break;

    case MovementStates::MOVING_RIGHT:
      this->monster_anim_right.play(dt);
      break;

    case MovementStates::MOVING_UP:
      this->monster_anim_right.play(dt);
      break;

    case MovementStates::MOVING_DOWN:
      this->monster_anim_right.play(dt);
      break;

    default:
      //do nothing
     break;
  }
  //this->logic.setMovementState(MovementStates::IDLE);
}




//load the itemsprites from the current room
void GameView::loadItemSprites(){
  Room tempRoom = levelManager.getCurrentRoom();
  for(int i = 0; i < tempRoom.getItems().size(); i++) {

    ItemActor* item = tempRoom.getItems().at(i);
    if(item->getActiveStatus()){
      itemSprites.push_back(new sf::Sprite);

      texture_item = itemTextures[item->getItemName()];
      itemSprites.back()->setTexture(*texture_item);
      itemSprites.back()->setPosition(item->getPosition().x, item->getPosition().y);
    }

  }
}


void GameView::setLogic(GameView& logic){}


void GameView::monsterSpriteAndSounds(){
  //If the monster is in the same room a the player
  if (this->logic.playerAndMonsterInSameRoom()) {
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
    this->dialogueBox.setSize(sf::Vector2f(900, 40));
    this->dialogueBox.setOutlineColor(sf::Color::White);
    this->dialogueBox.setOutlineThickness(2);

    sf::Vector2f myPos = sf::Vector2f(position.x - this->dialogueBox.getSize().x/2, 550);

    dialogueBox.setPosition(myPos);
}

//set the text for the dialoguebox
void GameView::setText(std::string words){
  this->message.setString(words);
  this->message.setCharacterSize(20);
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



void GameView::loadItemTextures(){
  std::string str;
  ifstream infile;
  infile.open ("../data/itemImageFiles.txt");
  while(!infile.eof())
  {
    std::getline(infile, str);
    std::string filepath = "../data/itemSprites/" + str + ".png";

    itemTextures[str] = new sf::Texture;

    if(!itemTextures[str]->loadFromFile(filepath)) {
      printf("incorrect file format");
    }

  }
  infile.close();
}

void GameView::setUpInventoyDisplay(){
  string inventoryDisplay_file = "../data/inventory_display.png";
  if(!texture_inventoryDisplay.loadFromFile(inventoryDisplay_file)){
    printf("incorrect file format");
  }
  sprite_inventoryDisplay.setTexture(texture_inventoryDisplay);
  sprite_inventoryDisplay.setPosition(800, 150);
  sprite_inventoryDisplay.setScale(sf::Vector2f(0.50f, 0.50f));

  setCounterText(holyWaterCounter_text,165);
  setCounterText(noteCounter_text, 265);
  setCounterText(keyCounter_text, 365);

}

void GameView::setCounterText(sf::Text& myText, float yPos){
  myText.setString("0");
  myText.setCharacterSize(60);
  myText.setFillColor(sf::Color(200, 200, 200));
  myText.setFont(font);
  myText.setPosition(sf::Vector2f(860, yPos));
}
