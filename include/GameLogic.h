#include <string>
#include <iostream>
#include "PlayerActor.h"

class GameLogic{

  private:
    PlayerActor player;

  public:
    GameLogic();

    void setup();

    //creates player object
    void createPlayer();

    //reutrns player object
    PlayerActor getPlayer();

    //Function for when the Up key is pressed
    void upPressed();

    //Function for when the Down key is pressed
    void downPressed();

    //Function for when the Left key is pressed
    void leftPressed();

    //Function for when the Right key is pressed
    void rightPressed();

};
