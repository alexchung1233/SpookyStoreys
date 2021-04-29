#ifndef SCRIPT_COMMAND_H // include guard
#define SCRIPT_COMMAND_H
#include <string>
#include <vector>
using namespace std;

class ScriptCommand
{


public:
    enum Commands {FADE_IN, FADE_OUT, MOVE_PLAYER_UP, MOVE_PLAYER_DOWN,
    MOVE_PLAYER_LEFT, MOVE_PLAYER_RIGHT, WAIT, PLAY_SOUND};

    enum Statuses {UNINIT, RUNNING, SUCCESS};

    ScriptCommand(){};
    ScriptCommand(vector<string>& data, int commandType);
    ~ScriptCommand() {};
    int getCommandType(){return commandType;}
    vector<string> getData(){return data;}
    //gets the current status of the command
    int getStatus() {return status;}
    void setStatus(int status) {this->status = status;}


private:
    int commandType;
    vector<string> data;
    int status;


};

#endif /* MY_CLASS_H */
