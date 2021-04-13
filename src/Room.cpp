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
        getline(infile,STRING); // Saves the line in STRING.
        vector<string> result;
		stringstream s_stream(STRING); //create string stream from the string
		
		while(s_stream.good()) {
			string substr;
			getline(s_stream, substr, ','); //get first string delimited by comma
			result.push_back(substr);
		}

		int posObj[4] = {-1, -1, -1, -1};

		for(int i = 0; i<result.size(); i++) {    //print all splitted strings
			cout << result.at(i) << endl;
			if(i>0){
				if(!result.at(0).find("ROOM")){
					myBoundaries[i-1] = stoi(result.at(i));
				}
				else{
					myObjects[i-1] = stoi(result.at(i));
				}
			}
		}
		// if(posObj[0] != -1){
		// 	myObjects.push_back( posObj );
		// }
    }
	infile.close();
}
