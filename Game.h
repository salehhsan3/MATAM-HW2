#ifndef GAME_H_
#define GAME_H_

#include "Character.h"



namespace mtm
{
    class Game
    {
    public:
        Game(int height, int width);
        ~Game();
        Game(const Game &other);
        void move(const GridPoint & src_coordinates,  const GridPoint & dst_coordinates);
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, 
                            units_t health, units_t ammo, units_t range, units_t power);
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void reload(const GridPoint & coordinates);
        bool isOver(Team* winningTeam=NULL) const;
        bool isCellOcupied(const GridPoint &dst_coordinates);
        std::shared_ptr<Character> findCharacterAtCoordinates(const GridPoint &coordinates);
        bool isCellOnGameBoard(const GridPoint &coordinates);
        void removeDeadPlayers();
        Game& operator=(const Game &other);
        friend std::ostream& operator<<(std::ostream& os, const Game& game);                               



    private:
        int height;
        int width;
        std::vector<std::vector<std::shared_ptr<Character>>> gameboard;
        
        // friend class Character;


    };
    
    
    
    

}




#endif