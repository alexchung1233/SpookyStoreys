#ifndef ITEM_ACTOR_H // include guard
#define ITEM_ACTOR_H
#include <SFML/Graphics.hpp>
#include "Position.h"
#include "Actor.h"
#include "PlayerActor.h"
#include "DialogueBox.h"

using namespace std;
class ItemActor : public Actor {
	public:
		// pure virtual function

		//gets the position of the item
		virtual Position getPosition() = 0;

		//sets myDialogue to be equal to dialogue
		virtual void setDialogue(string dialogue) = 0;

		//returns myDialogue
		virtual string getDialogue() = 0;

		//checks to see if the player is next to/near the item (using nextToPlayer helper function)
		//and, if they are, then returns the proper dialogue (if any) and runs the appropriate
		//actions, such as checking if the player has a key, if the ItemActor should be destroyed,
		//and so on
		virtual string interact(PlayerActor &player) = 0;

		std::string getSpriteFile(){ return filepath; }  
	
	protected:
		//helper function for interact()
		//returns true if the item is next to the player, false if otherwise
     	virtual bool nextToPlayer(PlayerActor &player) = 0;
    	
    	string myDialogue;
        string filepath;

	private:
};

#endif /* MY_CLASS_H */
