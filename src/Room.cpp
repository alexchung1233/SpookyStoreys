#include "Room.h"
#include <vector>


using namespace std;


Room::Room(){
}

void Room::setUpRoom(){
	string STRING;
	ifstream infile;
	infile.open ("../data/room_data.txt");
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
		else{
			sf::IntRect posObj;

			posObj.left = stoi(result.at(1));
			posObj.top = stoi(result.at(2));
			posObj.width = stoi(result.at(3));
			posObj.height = stoi(result.at(4));
			myObjects.push_back( posObj );
		}

    }
	infile.close();
}
