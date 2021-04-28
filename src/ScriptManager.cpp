#include "ScriptManager.h"

using namespace std;

//reads in the script and processes each command to their corresponding commandtype
void ScriptManager::readInScript(std::string scriptFileName){
  string directory = "../data/";
  string txt = ".txt";

  string STRING;
  string filepathTXT = directory + scriptFileName + txt;
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

    //pushes into the queue a new scriptcommand
    if(result.at(0) == "FADE_IN")
      scriptQueue.push(new ScriptCommand(result, ScriptCommand::FADE_IN));
    else if(result.at(0) == "MOVE_PLAYER_UP")
      scriptQueue.push(new ScriptCommand(result, ScriptCommand::MOVE_PLAYER_UP));

    }

  infile.close();
}
