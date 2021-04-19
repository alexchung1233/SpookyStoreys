#ifndef STATE_H // include guard
#define STATE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//represents a view state
class State
{
protected:
  int status;
  State* childState;

public:
  enum Statuses {UNINIT, RUNNING, PAUSED, SUCCESS, FAILED, ABORTED};
  //fix this issue
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

  bool isDead() {return status == SUCCESS | FAILED | ABORTED;}

  int getStatus() {return status;};

  bool hasChildState() {return childState != NULL;}

  State* getChildState() {return childState;}



protected:
  sf::RenderWindow* App;
  sf::Event Event;


};
#endif
