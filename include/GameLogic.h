#include <string>
#include <iostream>
#include "PlayerActor.h"
#include "Room.h"
#include "HolyWater.h"
#include "DialogueBox.h"



class GameLogic{

  private:
    PlayerActor player;
    Room myRoom;
    DialogueBox dialogue;
    HolyWater water;
    int Etracker;


  public:
    GameLogic();

    void setup();

    //creates player object
    void createPlayer();
    void createWater();
    void createDialogueBox();
    

    //reutrns player object
    PlayerActor getPlayer();
    DialogueBox getDialogueBox();
    HolyWater getWater();

    bool detectCollisionUp(float dt);
    bool detectCollisionDown(float dt);
    bool detectCollisionLeft(float dt);
    bool detectCollisionRight(float dt);


    void EPressed();

    //Function for when the Up key is pressed
    void upPressed(float dt);

    //Function for when the Down key is pressed
    void downPressed(float dt);

    //Function for when the Left key is pressed
    void leftPressed(float dt);

    //Function for when the Right key is pressed
    void rightPressed(float dt);

    void setRoom(Room room);


};
