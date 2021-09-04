#include "Character.h"
#include "Exceptions.h"



namespace mtm
{


    // Character::Character() : health(0),ammo(0),power(0),range(0) {};//valid values?
    Character::Character(units_t health, units_t ammo, units_t power, units_t range, Team team,
    GridPoint coordinates): health(health),ammo(ammo),power(power),range(range),team(team),coordinates(coordinates)
    {
        if (health <= 0 || ammo < 0 || power < 0 || range < 0) 
        {
            throw mtm::IllegalArgument();
        }
        
    }
    
    Character::~Character()
    {
    }
    // void attackNearByPlayerIfYouHaveTheAbility(std::shared_ptr<Character> temp_target,
    //                                                                 const GridPoint &dst_coordinates)
    // {
    //     //for normal characters they shouldn't be able to attack multiple characters, only
    //     // those that are gifted like soldier may do that!
    //     return;
    // }

    






}


