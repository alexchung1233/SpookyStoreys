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
    void upPressed(float dt);

    //Function for when the Down key is pressed
    void downPressed(float dt);

    //Function for when the Left key is pressed
    void leftPressed(float dt);

    //Function for when the Right key is pressed
    void rightPressed(float dt);

};
