#ifndef MEDIC_H_
#define MEDIC_H_

#include "Character.h"




namespace mtm
{
    class Medic : public Character
    {
        private:
        const int AMMO_RELOAD = 5;
        const int MAX_DISTANCE = 5;
        const int MODULO = 3;

        public:
        Medic() = default;
        Medic(units_t health, units_t ammo, units_t power, units_t range, Team team);
        Medic(const Medic& medic);
        Medic& operator=(const Medic& medic);
        virtual void reload() override;
        virtual void attack(std::shared_ptr<Character> temp_target, std::shared_ptr<Character> main_target,
            const GridPoint & src_coordinates, const GridPoint & dst_coordinates, bool &can_keep_attacking);
        bool isInStraightLine(const GridPoint src_coordinates, const GridPoint dst_coordinates);
        void attack(std::shared_ptr<Character> target, const GridPoint & dst_coordinates);
        bool isMovingDistanceLegal(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        virtual std::string fillCharacterSymbol() override;
        std::shared_ptr<Character> clone() const;



 
       
    };
}




#endif