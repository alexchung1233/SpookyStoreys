#include "ScriptCommand.h"

//script command is used to run a single game event within a queue based system.
ScriptCommand::ScriptCommand(vector<string>& data, int commandType){
  this->data = data;
  this->commandType = commandType;
  this->status = UNINIT;

}
