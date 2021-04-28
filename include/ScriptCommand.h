#ifndef SCRIPT_COMMAND_H // include guard
#define SCRIPT_COMMAND_H
#include <string>
#include <vector>
using namespace std;

class ScriptCommand
{


public:
    ScriptCommand(){};
    ScriptCommand(vector<string>& data, int commandType);
    enum Commands {FADE_IN, FADE_OUT, MOVE_PLAYER_UP, MOVE_PLAYER_DOWN,
    MOVE_PLAYER_LEFT, MOVE_PLAYER_RIGHT};
    ~ScriptCommand() {};
    int getCommandType(){return commandType;}
    vector<string> getData(){return data;}



private:
    int commandType;
    vector<string> data;



};

#endif /* MY_CLASS_H */
