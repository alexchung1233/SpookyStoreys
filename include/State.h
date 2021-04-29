#ifndef STATE_H // include guard
#define STATE_H
#include <SFML/Graphics.hpp>
#include "AudioManager.h"

//represents a view state
class State
{
protected:
  int status;
  State* childState = NULL;

public:
  enum Statuses {UNINIT, RUNNING, PAUSED, SUCCESS, FAILED, ABORTED};
  State() {};
  State(sf::RenderWindow& app);
  virtual ~State();

  //initalizes the state
  virtual void init();

  //pauses the state
  virtual void pause()=0;

  //unpauses the state
  virtual void unpause()=0;

  //updates the state by deltatime and event
  virtual void update(sf::Event& Event, float dt)=0;

  //renders the state onto the winodw
  virtual void render()=0;

  //checks if the state is done or not
  bool isDead() {return status == SUCCESS | status == FAILED | status == ABORTED;}

  //gets the current status of the state
  int getStatus() {return status;};

  //checks if the state has a child state, or essentially the next state
  bool hasChildState() {return childState != NULL;}

  State* getChildState() {return childState;}



protected:
  sf::RenderWindow* App;
  sf::Event Event;
  AudioManager* audioManager;


};
#endif
