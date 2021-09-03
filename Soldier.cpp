#include "Soldier.h"




namespace mtm
{
//     Soldier::Soldier();
    Soldier::Soldier(units_t health, units_t ammo, units_t power, units_t range, Team team)
     : Character(health,ammo,power,range,team)
    {

    }
    
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

    void Soldier::attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool &can_keep_attacking)
    {
        if ( (this->ammo) <= 0)
        {
            throw OutOfAmmo();
        }
        if ( isInStraightLine(src_coordinates,dst_coordinates) == false)
        {
            throw IllegalTarget();
        }
        if ( main_target == nullptr )
        {
            (this->ammo)--;
        }
        // if ((temp_target != nullptr) && (GridPoint::distance(temp_target->coordinates,dst_coordinates) == 0) )
        // {
        //     if ( temp_target->team != this->team )
        //     {
        //         (temp_target->health) -= power;
        //         (this->ammo)--;
        //     }
        // }
        int ceil_modulo_range = (range%MODULO_RANGE) ? (((this->range)/MODULO_RANGE)+1) : (this->range)/MODULO_RANGE;
        if ( (temp_target != nullptr) && 
                (GridPoint::distance(temp_target->coordinates,dst_coordinates)  <= ceil_modulo_range )
                && (GridPoint::distance(temp_target->coordinates,dst_coordinates) > 0 ) )
        {
            if ( temp_target->team != this->team )
            {
                int ceil_half_power = (!(power%MODULO_POWER)) ? (power/MODULO_POWER) : ((power/MODULO_POWER)+1);
                (temp_target->health) -= ceil_half_power;//need to use ceil?
            }
        }
        can_keep_attacking = true;
        return;
    }

    void Soldier::reload() 
    {
        this->ammo += AMMO_RELOAD;
        return;
    }

    std::string Soldier::fillCharacterSymbol()
    {
        if ( this->team == POWERLIFTERS)
        {
            return "S";
        }
        //else
        return "s";
    }

    std::shared_ptr<Character> Soldier::clone() const
    {
        // return(std::shared_ptr<Soldier>(new mtm::Soldier(*this)));
        return(std::shared_ptr<Soldier>(new mtm::Soldier(this->health,this->ammo,this->power,this->range,this->team)));
    }

}