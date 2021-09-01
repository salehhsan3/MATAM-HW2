
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



    void Medic::attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool *can_reduce_ammo)
    {
        int distance = GridPoint::distance ( src_coordinates,dst_coordinates);
        if (distance == 0 || main_target == nullptr)//he can't attack himself or an empty coordinate
        {
            throw IllegalTarget();
        }
        if ( (distance <= this->range) )//do I even need to check for this, because we did that in the main function in Game
        {        
            if ( GridPoint::distance(temp_target->coordinates,dst_coordinates) == 0 )
            {
                if ( (this->ammo > 0) &&  ( temp_target->team != this->team ) && 
                                    ( temp_target->coordinates != this->coordinates ) )
                {
                    (temp_target->health) -= power;
                    (*can_reduce_ammo) = true;
                }
            }
            if ( (this->ammo > 0) &&  ( temp_target->team == this->team ) && 
                                    ( temp_target->coordinates != this->coordinates ) )
            {
                if ( (this->ammo > 0) && ( temp_target->team != this->team ) &&
                                    ( temp_target->coordinates != this->coordinates ) )
                {
                    (temp_target->health) += power;
                    (*can_reduce_ammo) = false;
                }
            }
        }
        return;
    }

    Medic::Medic(units_t health, units_t ammo, units_t power, units_t range, Team team)
     : Character(health,ammo,power,range,team)
    {

    }
    


    bool Medic::isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        if (GridPoint::distance(src_coordinates,dst_coordinates) <= (this->MAX_DISTANCE) )
        {
            return true;
        }
        return false;
    }


};