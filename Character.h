#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Auxiliaries.h"

namespace mtm
{


    class Character
    {
    public:
        Character() = default;//needs to be in the cpp file?
        Character(units_t health, units_t ammo, units_t power, units_t range, Team team,
                                                GridPoint coordinates = GridPoint(-1,-1));
        ~Character();// = default, there is no need for a special constructor because I dont allocate memory!
        Character& operator=(const Character& character) = default;
        // virtual void attack(const Character& character, units_t damage) = 0;
        // virtual void attack(const GridPoint & dst_coordinates) = 0;
        virtual void attack(std::shared_ptr<Character> target, const GridPoint & src_coordinates,
                                            const GridPoint & dst_coordinates, bool *can_reduce_ammo) = 0;
        virtual void reload() = 0;
        virtual bool isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) = 0;
        void decrementAmmoAfterAttack(Character &attacker);
        // the reason this(reload) is a pure virtual function 
        //is because AMMO_RELOAD values change from character to character

    protected:
        units_t health;
        units_t ammo;
        units_t power;
        units_t range;
        Team team;
        GridPoint coordinates;

        friend class Game;
        friend class Soldier;
        friend class Medic;
        friend class Sniper;

    };
    
    

};











#endif