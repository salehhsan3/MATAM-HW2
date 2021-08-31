#ifndef SNIPER_H_
#define SNIPER_H_

#include "Character.h"




namespace mtm
{
    class Sniper : public Character
    {
        private:
        const int AMMO_RELOAD = 2;
        const int MAX_DISTANCE = 4;
        GridPoint coordinates;
        friend class Game;//needed?


        public:
        Sniper() = default;//it said there was an error because there was no default c'tor
        Sniper(units_t health, units_t ammo, units_t power, units_t range, Team team,
                                                GridPoint coordinates = GridPoint(-1,-1));
        Sniper(const Sniper& medic);   
        Sniper& operator=(const Sniper& sniper);
        virtual void reload() override;//override needed?
        void attack(std::shared_ptr<Character> target, const GridPoint & dst_coordinates);


 
       
    };
};




#endif