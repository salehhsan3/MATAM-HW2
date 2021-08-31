#include "Soldier.h"




namespace mtm
{
//     Soldier::Soldier();
    Soldier::Soldier(units_t health, units_t ammo, units_t power, units_t range, Team team, GridPoint coordinates)
     : Character(health,ammo,power,range,team), coordinates(coordinates)
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
                                                                const GridPoint & dst_coordinates)
    {
        int distance = GridPoint::distance ( src_coordinates,dst_coordinates);
        if ( ( isMovingDistanceLegal(src_coordinates,dst_coordinates) == true ) 
                && ( isInStraightLine(src_coordinates,dst_coordinates) == true) )
        {
            // if (distance == 0)
            // {
                // it means that he's attacking himself, reduce ammo and look for people nearby
                // and give them damage in case they deserve it
                // I believe that there is no need for this check, I can just damage people
                // who are at a distance > 0 and < MAX_DISTANCE/3
            // }
            if ( GridPoint::distance(target->coordinates,dst_coordinates) == 0 )
            {
                if ( (this->ammo > 0) && ( target->coordinates != this->coordinates ))
                {
                    (this->ammo)--;
                    (target->health) -= power;
                }
                else
                {
                    (this->ammo)--;                
                }
            }
            if ( (GridPoint::distance(target->coordinates,dst_coordinates)  <= (this->range)/3)
                    && (GridPoint::distance(target->coordinates,dst_coordinates)  > 0) )
            {
                //incomplete : have to check the distances correctly,
                // make sure to do int conversions according to what was asked!
                if ( (this->ammo > 0) && ( target->coordinates != this->coordinates ))
                {
                    (this->ammo)--;
                    (target->health) -= power/2;
                }
            }
            
               
        }
        
    }

    void Soldier::reload() 
    {
        //I implemented this function in all 3 characters I have, and it's the exact same Implementation
        //is it considered as code duplication? and how can I solve it if yes?
        this->ammo += AMMO_RELOAD;
        return;
    }

    

};