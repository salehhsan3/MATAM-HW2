
#include "Character.h"
#include "Sniper.h"


namespace mtm
{



    void Sniper::reload() 
    {
        this->ammo += AMMO_RELOAD;
        return;
    }
    void Sniper::attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool &can_keep_attacking)
    {
        // int distance = GridPoint::distance ( src_coordinates,dst_coordinates);
        if (main_target == nullptr || (main_target->team == this->team) )
        {
            throw IllegalTarget();
        }
        bool bool_to_int = (this->range)%MODULO_RANGE;
        int min_distance = (  (this->range)/MODULO_RANGE +  bool_to_int );
        int max_distance = this->range;
        if( ( GridPoint::distance(main_target->coordinates,this->coordinates) < min_distance  )
                || ( GridPoint::distance(main_target->coordinates,this->coordinates) > max_distance ) )
        {
            throw OutOfRange();
        }

        if (this->ammo <= 0)
        {
            throw OutOfAmmo();
        }

        //if we're here then we can attack the target
        (main_target->health) -= power;
        (this->hit_targets)++;
        if ( (this->hit_targets%MODULO_HITS) == 0 && (this->hit_targets != 0) )
        {
            //in order to deal double power!
            (main_target->health) -= power;
        }
        (this->ammo)--;// for Sniper as long as we launched an attack we can reduce ammo
        can_keep_attacking = false;
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

    std::string Sniper::fillCharacterSymbol()
    {
        if ( this->team == POWERLIFTERS)
        {
            return "N";
        }
        //else
        return "n";
    }


    std::shared_ptr<Character> Sniper::clone() const
    {
        // return(std::shared_ptr<Sniper>(new mtm::Sniper(*this)));
        return(std::shared_ptr<Sniper>(new mtm::Sniper(this->health,this->ammo,this->power,this->range,this->team)));
    }


}