#include "ScriptManager.h"

using namespace std;



/*
How to use commands. Put the command name and values seperated by a comma

Example
FADE_IN,5.0,0,0,0

this fades in for 5 seconds using the rgb values 0,0,0


FADE_IN,float time,int red,int green, int blue
fades the screen in

WAIT,float time
pauses the game event for a certain amount of time

SHOW_DIALOGUE,string dialogue message(no quotes needed, just the raw text)
  this shows the dialogue of the player, interact with E

PLAY_SOUND,string path name
  this plays a sound

PAUSE_MONSTER
  this pauses the monster so it doesn't do anything

START_MONSTER
  this starts the monster so it does do stuff

WIP:
MOVE_PLAYER_UP
MOVE_PLAYER_LEFT
MOVE_PLAYER_RIGHT
MOVE_PLAYER_DOWN
LOCK_PLAYER

*/


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
    else if(result.at(0) == "WAIT")
      scriptQueue.push(new ScriptCommand(result, ScriptCommand::WAIT));
    else if(result.at(0) == "PLAY_SOUND")
      scriptQueue.push(new ScriptCommand(result, ScriptCommand::PLAY_SOUND));
    else if(result.at(0) == "SHOW_DIALOGUE")
      scriptQueue.push(new ScriptCommand(result, ScriptCommand::SHOW_DIALOGUE));
    else if(result.at(0) == "PAUSE_MONSTER")
      scriptQueue.push(new ScriptCommand(result, ScriptCommand::PAUSE_MONSTER));
    else if(result.at(0) == "START_MONSTER")
      scriptQueue.push(new ScriptCommand(result, ScriptCommand::START_MONSTER));
    }

  infile.close();
}
