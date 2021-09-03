#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Auxiliaries.h"

namespace mtm
{


    class Character
    {
    public:
        Character() = default;
        Character(units_t health, units_t ammo, units_t power, units_t range, Team team,
                         GridPoint coordinates = GridPoint(-1,-1));
        //is it okay to have default type as MEDIC and coordinate as (-1,-1)
        ~Character();
        Character& operator=(const Character& character) = default;
        virtual void attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool &can_keep_attacking) = 0;
        virtual void reload() = 0;
        virtual bool isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) = 0;
        // void decrementAmmoAfterAttack(std::shared_ptr<Character> attacker);
        virtual std::string fillCharacterSymbol() = 0;
        std::shared_ptr<Character> virtual clone() const = 0;


    protected:
        units_t health;
        units_t ammo;
        units_t power;
        units_t range;
        Team team;
        GridPoint coordinates;
        //CharacterType type;//maybe a bad idea

        friend class Game;
        friend class Soldier;
        friend class Medic;
        friend class Sniper;

    };
    
    

}











#endif