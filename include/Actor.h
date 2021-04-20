#ifndef ACTOR_H // include guard
#define ACTOR_H
#include "Position.h"
#include <string>
#include <iostream>

class Actor
{
public:
<<<<<<< HEAD
  Actor(int actorId) {actorId = id;}
  Actor(){};
  //virtual void init();
  //virtual bool update(float deltaMs);
  //virtual void destroy();
=======
	Actor(int actorId) {actorId = id;}
	Actor(){};
	//virtual void init();
	//virtual bool update(float deltaMs);
	//virtual void destroy();

	virtual sf::Vector2f getSize() = 0;
	virtual void setSize(sf::Vector2f size) = 0;
	virtual void setSize(float x, float y) = 0;


>>>>>>> adding_game_states

protected:
	Position position;
	int id;
	
	sf::Vector2f mySize;

};
#endif