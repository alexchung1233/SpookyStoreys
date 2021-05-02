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
		ItemActor() {};
		~ItemActor(){};

		//gets the position of the item
		virtual Position getPosition() = 0;

		virtual void init() = 0;


		//sets myDialogue to be equal to dialogue
		void setDialogue(string dialogue) { this->myDialogue = dialogue; }

		//returns myDialogue
		string getDialogue() { return this->myDialogue; }

		//checks to see if the player is next to/near the item (using nextToPlayer helper function)
		//and, if they are, then returns the proper dialogue (if any) and runs the appropriate
		//actions, such as checking if the player has a key, if the ItemActor should be destroyed,
		//and so on
		virtual string interact(PlayerActor &player) = 0;

		std::string getItemName() { return itemName; }

		virtual bool destroyable() { return canBeDestroyed; }

		//helper function for interact()
		//returns true if the item is next to the player, false if otherwise
     	virtual bool nextToPlayer(PlayerActor &player) = 0;
	
	protected:
    	string myDialogue;
        string itemName;
        bool canBeDestroyed;

	private:
};

#endif /* MY_CLASS_H */
