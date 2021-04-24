#include "Room.h"
#include <vector>


using namespace std;


Room::Room(){
}

void Room::setUpRoom(std::string filepath){
	string STRING;
	ifstream infile;
	infile.open (filepath);
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
			for(int i = 1; i < result.size(); i++)
				myDoor.push_back( result.at(i) );
		}
		
    }
	infile.close();
}

sf::IntRect Room::getBoundaries(){
	return myBoundaries;
}

std::vector<sf::IntRect> Room::getObstacles(){
	return myObstacles;
}
