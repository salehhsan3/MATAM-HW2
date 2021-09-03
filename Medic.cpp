
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
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool &can_keep_attacking)
    {
        int distance = GridPoint::distance ( src_coordinates,dst_coordinates);
        if (this->ammo <= 0)
        {
            throw OutOfAmmo();
        }
        if (distance == 0 || main_target == nullptr)//he can't attack himself or an empty coordinate
        {
            throw IllegalTarget();
        }

        if ( (main_target != nullptr) && GridPoint::distance(main_target->coordinates,dst_coordinates) == 0 )
        {
            if ( main_target->team != this->team )
            {
                (main_target->health) -= power;
                (this->ammo)--;
            }
        }
        if ( ( main_target->team == this->team ) && ( main_target->coordinates != this->coordinates ) )
        {
            (main_target->health) += power;
        }
        can_keep_attacking = false;
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

    std::string Medic::fillCharacterSymbol()
    {
        if ( this->team == POWERLIFTERS)
        {
            return "M";
        }
        //else
        return "m";
    }

    std::shared_ptr<Character> Medic::clone() const
    {
        // return(std::shared_ptr<Medic>(new mtm::Medic(*this)));
        return(std::shared_ptr<Medic>(new mtm::Medic(this->health,this->ammo,this->power,this->range,this->team)));
    }

}