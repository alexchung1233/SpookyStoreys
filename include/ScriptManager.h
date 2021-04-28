#ifndef SCRIPT_MANAGER_H // include guard
#define SCRIPT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "ScriptManager.h"
#include "ScriptCommand.h"



class ScriptManager
{
    public:
        ScriptManager(){};
        void readInScript(std::string scriptFileName);
        std::queue<ScriptCommand*> scriptQueue;

    private:





};



#endif /* MY_CLASS_H */
