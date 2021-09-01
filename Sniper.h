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
        int hit_targets = 0;
        // GridPoint coordinates;
        friend class Game;//needed?


        public:
        Sniper() = default;//it said there was an error because there was no default c'tor
        Sniper(units_t health, units_t ammo, units_t power, units_t range, Team team);
        Sniper(const Sniper& medic);   
        Sniper& operator=(const Sniper& sniper);
        virtual void reload() override;//override needed?
        virtual void attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool *can_reduce_ammo);
        bool isInStraightLine(const GridPoint src_coordinates, const GridPoint dst_coordinates);
        void attack(std::shared_ptr<Character> target, const GridPoint & dst_coordinates);
        bool isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);


 
       
    };
};




#endif