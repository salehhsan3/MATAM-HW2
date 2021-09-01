#include "Soldier.h"




namespace mtm
{
//     Soldier::Soldier();
    Soldier::Soldier(units_t health, units_t ammo, units_t power, units_t range, Team team, GridPoint coordinates)
     : Character(health,ammo,power,range,team,coordinates)
    {

    };
    
    Soldier::~Soldier()
    {
        
    }

    bool Soldier::isInStraightLine(const GridPoint src_coordinates, const GridPoint dst_coordinates)
    //should the paramaters be passed as references?? I tried however it gave me an error implying I should remove the reference!
    {
        if (src_coordinates.col == dst_coordinates.col || src_coordinates.row == dst_coordinates.row )
        {
            return true;
        }
        return false;
    }

    bool Soldier::isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        if (GridPoint::distance(src_coordinates,dst_coordinates) <= (this->MAX_DISTANCE) )
        {
            return true;
        }
        return false;
    }

    void Soldier::attack(std::shared_ptr<Character> target, const GridPoint & src_coordinates,
                                            const GridPoint & dst_coordinates, bool *can_reduce_ammo)
    {
        int distance = GridPoint::distance ( src_coordinates,dst_coordinates);
        bool in_straight_line = isInStraightLine(src_coordinates,dst_coordinates);
        if (in_straight_line == false)
        {
            throw IllegalTarget();
        }
        
        if ( (in_straight_line == true) && (distance <= this->range) )
        {        
            if ( GridPoint::distance(target->coordinates,dst_coordinates) == 0 )
            {
                if ( (this->ammo > 0) &&  ( target->team != this->team ) && 
                                    ( target->coordinates != this->coordinates ) )
                {
                    (target->health) -= power;
                }
            }
            if ( (GridPoint::distance(target->coordinates,dst_coordinates)  <= ( (this->range)/3) + (range%3) )
                    && (GridPoint::distance(target->coordinates,dst_coordinates)  > 0) )
            {
                if ( (this->ammo > 0) && ( target->team != this->team ) &&
                                    ( target->coordinates != this->coordinates ) )
                {
                    (target->health) -= (power/2);//need to use ceil?
                }
            }
            (*can_reduce_ammo) = true;//for soldier we can attack anything therefore always reduce
        }
        return;
    }

    void Soldier::reload() 
    {
        //I implemented this function in all 3 characters I have, and it's the exact same Implementation
        //is it considered as code duplication? and how can I solve it if yes?
        this->ammo += AMMO_RELOAD;
        return;
    }

    

};