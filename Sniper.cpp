
#include "Character.h"
#include "Sniper.h"


namespace mtm
{



    void Sniper::reload() 
    {
        //I implemented this function in all 3 characters I have, and it's the exact same Implementation
        //is it considered as code duplication? and how can I solve it if yes?
        this->ammo += AMMO_RELOAD;
        return;
    }
    void Sniper::attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool *can_reduce_ammo)
    {
        int distance = GridPoint::distance ( src_coordinates,dst_coordinates);
        if (main_target == nullptr)
        {
            throw IllegalTarget();
        }
        if ( distance <= this->range )
        {        
            if ( ( GridPoint::distance(temp_target->coordinates,dst_coordinates) == 0 )
                    && ( GridPoint::distance(temp_target->coordinates,this->coordinates)
                                                 >= ( (this->range) + ( (this->range)%2 ) ) )  )
            {
                if ( temp_target->team == this->team )
                {
                    throw IllegalTarget();
                }
                (temp_target->health) -= power;
                (this->hit_targets)++;
                if ( (this->hit_targets%3) == 0)
                {
                    //in order to deal double power!
                    (temp_target->health) -= power;
                }
                (*can_reduce_ammo) = true;// for Sniper as long as we launched an attack we can reduce ammo
            }
        }
        return;
    }

    Sniper::Sniper(units_t health, units_t ammo, units_t power, units_t range, Team team)
     : Character(health,ammo,power,range,team)
    {

    }
    


    bool Sniper::isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        if (GridPoint::distance(src_coordinates,dst_coordinates) <= (this->MAX_DISTANCE) )
        {
            return true;
        }
        return false;
    }



};