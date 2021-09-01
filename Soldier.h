#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "Character.h"


namespace mtm
{

    class Soldier : public Character
    {
    public:
        Soldier() = default;//it said there was an error because there was no default c'tor
        Soldier(units_t health, units_t ammo, units_t power, units_t range, Team team);
        ~Soldier();
        // virtual void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        bool isInStraightLine(const GridPoint src_coordinates, const GridPoint dst_coordinates);
        bool isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) override;
        virtual void reload() override;//override needed?
        // virtual void attack(const GridPoint & dst_coordinates) override;
        virtual void attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
                  const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool *can_reduce_ammo);
        void attackWithFullPower(std::shared_ptr<Character> target);
        void attackWithHalfPower(std::shared_ptr<Character> target);
        // Soldier& operator=(const Soldier &soldier) = default; // if it's default, then I believe there's no need to explicitly say it
        
    private:
        const int AMMO_RELOAD = 3;
        const int MAX_DISTANCE = 3;
        // GridPoint coordinates;
        friend class Character;//needed?
        // friend class Game;//needed?

    };
    

    




};















#endif