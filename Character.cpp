#include "Character.h"
#include "Exceptions.h"



namespace mtm
{


    // Character::Character() : health(0),ammo(0),power(0),range(0) {};//valid values?
    Character::Character(units_t health, units_t ammo, units_t power, units_t range, Team team)
     : health(health),ammo(ammo),power(power),range(range),team(team)
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
    // there was no need for this function to be here, I added it to Game.
    // void move(const GridPoint & src_coordinates,  const GridPoint & dst_coordinates)
    // {
    //     for ( int i = gameboard.begin(); i < gameboard.size() ; i++)
    //     {
    //         if ( ( *(gameboard[i]) ) == src_coordinates )
    //         {
    //             ( *(gameboard[i]) ).coordinates = dst_coordinates;
    //         }
            
    //     }
            
    // }

    // tried the following implementation so that I don't duplicate code however it was unsuccessful!
    // virtual void Character::reload()
    // {
    //     this->ammo += AMMO_RELOAD;
    // }


    






};


