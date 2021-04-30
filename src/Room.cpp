#include "Room.h"
#include <vector>


using namespace std;


Room::Room(){
}

Room::Room(std::string roomName){
	setUpRoom(roomName);
}

void Room::setUpRoom(std::string roomName){
	string directory = "../data/";
	string txt = ".txt";
	string png = ".png";
	
	string STRING;
	string filepathTXT = directory + roomName + txt;
	ifstream infile;
	infile.open (filepathTXT);
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile, STRING); // Saves the line in STRING.
        vector<string>result;
		stringstream s_stream(STRING); //create string stream from the string
		
		while(s_stream.good()) {
			string substr;
			getline(s_stream, substr, ','); //get first string delimited by comma
			result.push_back(substr);
		}

		if(!result.at(0).find("ROOM")){
			myBoundaries.left = stoi(result.at(1));
			myBoundaries.top = stoi(result.at(2));
			myBoundaries.width = stoi(result.at(3));
			myBoundaries.height = stoi(result.at(4));
		}
		else if (!result.at(0).find("OBST")){
			sf::IntRect posObst;

			posObst.left = stoi(result.at(1));
			posObst.top = stoi(result.at(2));
			posObst.width = stoi(result.at(3));
			posObst.height = stoi(result.at(4));
			myObstacles.push_back( posObst );
		}
		else if (!result.at(0).find("DOOR")){
			vector<string>forDoor;
			for(int i = 1; i < result.size(); i++){
				forDoor.push_back(result.at(i));
			}
			Door myDoor(forDoor);
			myDoors.push_back( myDoor );
		}
		else if (!result.at(0).find("HOLYWATER")){
			vector<string>forWater;
			for(int i = 1; i < result.size(); i++){
				forWater.push_back(result.at(i));
			}
			HolyWater myWater(forWater);
			myWater.init();
			myWaters.push_back(myWater);

		}
		
    }
	infile.close();

	string filepathPNG = directory + roomName + png;

  	if(!levelTexture.loadFromFile(filepathPNG)){
    	printf("incorrect file format");
  	}

	this->createDialogueBox();
	dialoguebox = this->getDiaogueBox();

}

sf::IntRect Room::getBoundaries(){
	return myBoundaries;
}

std::vector<sf::IntRect> Room::getObstacles(){
	return myObstacles;
}

sf::Texture Room::getTexture(){
	return levelTexture;
}

std::vector<Door> Room::getDoors(){
	return myDoors;
}

std::vector<HolyWater>* Room::getWaters(){
	return &myWaters;
}

DialogueBox Room::getDiaogueBox(){
	return dialoguebox;
}

void Room::createDialogueBox(){
	int sampleLimit = 2;
	dialoguebox = DialogueBox(sampleLimit);
	dialoguebox.init();
}
