#include "Character.h"
#include "Exceptions.h"



namespace mtm
{


    // Character::Character() : health(0),ammo(0),power(0),range(0) {};//valid values?
    Character::Character(units_t health, units_t ammo, units_t power, units_t range, Team team,
     GridPoint coordinates): health(health),ammo(ammo),power(power),
                                        range(range),team(team),coordinates(coordinates)
    {
        if (health <= 0 || ammo < 0 || power < 0 || range <= 0) 
        {
            // is range allowed to be 0? what about team could he receive an illegal argument?
            throw mtm::IllegalArgument();
        }
        
    }
    
    Character::~Character()
    {
    }
    void Character::decrementAmmoAfterAttack(std::shared_ptr<Character> attacker)
    {
        (attacker->ammo)--;
        return;
    }


    






};


