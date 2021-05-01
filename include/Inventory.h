#ifndef INVENTORY_H // include guard
#define INVENTORY_H

#include <string>
#include <iostream>
#include <map>

class Inventory
{
    public:
        Inventory();
        void init();
        
        void upHolyWaterCount();
        void downHolyWaterCount();
        int getHolyWaterCount();

        void foundNewNote(int noteID);
        int numNotesFound();

        void foundFirepoker();
        bool hasFoundFirepoker();

        void foundKey();
        bool hasFoundKey();

        void foundWeapon();
        bool hasFoundWeapon();

    private:
        std::map<const std::string, bool> notesObtained;
        std::map<const std::string, bool> unlocksObtained;

        int holyWaterCount;

};

#endif /* MY_CLASS_H */
