#ifndef ITEM_ACTOR_H // include guard
#define ITEM_ACTOR_H
#include <SFML/Graphics.hpp>
#include "Position.h"
#include "Actor.h"

class ItemActor : public Actor {
   public:
      // pure virtual function
      virtual Position getPosition() = 0;
      virtual string getDialogue() = 0;
      virtual void setDialogue() = 0;
      virtual void move() = 0;
      
	protected:
    	string myDialogue;

	private:
};

#endif /* MY_CLASS_H */