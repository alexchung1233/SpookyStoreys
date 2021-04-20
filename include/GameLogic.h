#include <string>
#include <iostream>
#include "PlayerActor.h"

class GameLogic{

  private:
    PlayerActor player;

<<<<<<< HEAD
=======
  public:
    GameLogic();

>>>>>>> adding_game_states
    void setup();

    //creates player object
    void createPlayer();

<<<<<<< HEAD
  public:
    GameLogic();

    //reutrns player object
    PlayerActor getPlayer();

    void setDifficulty(int diff);

=======
    //reutrns player object
    PlayerActor getPlayer();

>>>>>>> adding_game_states
    //Function for when the Up key is pressed
    void upPressed(float dt);

    //Function for when the Down key is pressed
    void downPressed(float dt);

    //Function for when the Left key is pressed
    void leftPressed(float dt);

    //Function for when the Right key is pressed
    void rightPressed(float dt);

};
