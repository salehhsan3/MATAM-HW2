#ifndef MEDIC_H_
#define MEDIC_H_

#include "Character.h"




namespace mtm
{
    class Medic : public Character
    {
        private:
        const int AMMO_RELOAD = 5;
        const int MAX_DISTANCE = 5;
        // GridPoint coordinates;
        friend class Game;//needed?


        public:
        Medic() = default;//it said there was an error because there was no default c'tor
        Medic(units_t health, units_t ammo, units_t power, units_t range, Team team);
        Medic(const Medic& medic);
        Medic& operator=(const Medic& medic);
        virtual void reload() override;//override needed?
        virtual void attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool *can_reduce_ammo);
        bool isInStraightLine(const GridPoint src_coordinates, const GridPoint dst_coordinates);
        void attack(std::shared_ptr<Character> target, const GridPoint & dst_coordinates);
        bool isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);



 
       
    };
};




#endif