#include <string>
#include <iostream>
#include "PlayerActor.h"
#include "Room.h"
#include "HolyWater.h"
#include "DialogueBox.h"
#include "LevelManager.h"
#include "MovementStates.h"

class GameLogic{

  private:
    PlayerActor player;
    Room myRoom;

    bool officeUnlocked;

    bool hitsDoor(sf::IntRect possiblePlayerPosition);


  public:
    GameLogic() { showBox = false; };
    bool showBox;

    void setup();

    //creates player object
    void createPlayer();

    int Etracker;

    LevelManager* levelManager;


    //reutrns player object
    PlayerActor getPlayer();
    

    bool detectCollisionUp(float dt);
    bool detectCollisionDown(float dt);
    bool detectCollisionLeft(float dt);
    bool detectCollisionRight(float dt);

    void setLevelManager(LevelManager &LM);

    void setMovementState(MovementStates::movementStates state);

    void EPressed();
    void setUpDialogueBox(ItemActor* myItem, DialogueBox& myBox, float i);

    //Function for when the Up key is pressed
    void upPressed(float dt);

    //Function for when the Down key is pressed
    void downPressed(float dt);

    //Function for when the Left key is pressed
    void leftPressed(float dt);

    //Function for when the Right key is pressed
    void rightPressed(float dt);

    void update(float dt);

    void setRoom(Room room);

    int getPlayState();

};
