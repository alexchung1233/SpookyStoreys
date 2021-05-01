#include "Inventory.h"

using namespace std;

Inventory::Inventory(){

}

void Inventory::init(){
    holyWaterCount = 0;

    for(int i = 1; i <= 4; i++)
        notesObtained["note_" + to_string(i)] = false;

    unlocksObtained["firepoker"] = false;
    unlocksObtained["key"] = false;
    unlocksObtained["weapon"] = false;

}

void Inventory::upHolyWaterCount(){
    holyWaterCount++;
}

void Inventory::downHolyWaterCount(){
    holyWaterCount--;
}

int Inventory::getHolyWaterCount(){
    return holyWaterCount;
}

void Inventory::foundNewNote(int noteID){
    notesObtained["note_" + to_string(noteID)] = true;
}

int Inventory::numNotesFound(){
    int numFound = 0;
    for(int i = 1; i <= 4; i++)
        if(notesObtained["note_" + to_string(i)])
            numFound++;
    return numFound;
}

void Inventory::foundFirepoker(){
    unlocksObtained["firepoker"] = true;
}

bool Inventory::hasFoundFirepoker(){
    return unlocksObtained["firepoker"];
}

void Inventory::foundKey(){
    unlocksObtained["key"] = true;
}

bool Inventory::hasFoundKey(){
    return unlocksObtained["key"];
}

void Inventory::foundWeapon(){
    unlocksObtained["weapon"] = true;
}

bool Inventory::hasFoundWeapon(){
    return unlocksObtained["weapon"];
}