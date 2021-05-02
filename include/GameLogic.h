#include <string>
#include <iostream>
#include "PlayerActor.h"
#include "Room.h"
#include "ItemActor.h"
#include "DialogueBox.h"
#include "LevelManager.h"
#include "MovementStates.h"
#include "MonsterAI.h"

class GameLogic{

  private:
    PlayerActor player;
    Room myRoom;

    bool officeUnlocked;
    
    int WTracker;
    bool holyWaterUsed;

    ItemActor* currentNextToItem;

    bool hitsDoor(sf::IntRect possiblePlayerPosition);

    MonsterView monsterView;

    LevelManager* levelManager;

  public:
    GameLogic() { showBox = false; };
    
    bool showBox;

    MonsterAI monsterAI;

    MonsterView& getMonsterView();
    MonsterActor getMonsterActor();
    void setMonsterLevelManager(LevelManager &MLM);

    void setup();

    //creates player object
    void createPlayer();
    void createDialogueBox();

    int Etracker;

    //reutrns player object
    PlayerActor getPlayer();
    DialogueBox getDialogueBox();
    DialogueBox dialoguebox;

    bool detectCollisionUp(float dt);
    bool detectCollisionDown(float dt);
    bool detectCollisionLeft(float dt);
    bool detectCollisionRight(float dt);

    //Function for when the Up key is pressed
    void upPressed(float dt);
    //Function for when the Down key is pressed
    void downPressed(float dt);
    //Function for when the Left key is pressed
    void leftPressed(float dt);
    //Function for when the Right key is pressed
    void rightPressed(float dt);
    //Function for when W is pressed for holy water
    void WPressed();
    bool getHolyWaterUsed();

    bool isPlayerByItem();

    void setLevelManager(LevelManager &LM);

    void setMovementState(MovementStates::movementStates state);

    bool isDialogueBoxUsed();
    void setDialogueBoxStatus(bool status);

    void updateAI(float dt, bool inSameRoom);

    void setRoom(Room room);

    int getPlayState();

    bool dialogueBoxFinished();
    void postDialogueBoxUse();

};
