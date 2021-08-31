
#include "Character.h"
#include "Medic.h"


namespace mtm
{

    void Medic::reload() 
    {
        //I implemented this function in all 3 characters I have, and it's the exact same Implementation
        //is it considered as code duplication? and how can I solve it if yes?
        this->ammo += AMMO_RELOAD;
        return;
    }

};

               