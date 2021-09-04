#ifndef SOLDIER_H_
#define SOLDIER_H_

#include "Character.h"


namespace mtm
{

    class Soldier : public Character
    {
    public:
        Soldier() = default;
        Soldier(units_t health, units_t ammo, units_t power, units_t range, Team team);
        ~Soldier();
        bool isInStraightLine(const GridPoint src_coordinates, const GridPoint dst_coordinates);
        bool isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) override;
        virtual void reload() override;
        virtual void attack(std::shared_ptr<Character> main_target,const GridPoint & src_coordinates,
                                     const GridPoint & dst_coordinates, bool &can_keep_attacking);
       virtual void attackNearByPlayerIfYouHaveTheAbility(std::shared_ptr<Character> temp_target,
                                                        const GridPoint &dst_coordinates) override;
        void attackWithFullPower(std::shared_ptr<Character> target);
        void attackWithHalfPower(std::shared_ptr<Character> target);
        virtual std::string fillCharacterSymbol() override;
        std::shared_ptr<Character> virtual clone() const;
        
    private:
        const int AMMO_RELOAD = 3;
        const int MAX_DISTANCE = 3;
        const int MODULO_POWER = 2;
        const int MODULO_RANGE = 3;

    };
    

    




}















#endif