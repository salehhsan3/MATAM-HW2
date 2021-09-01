#include "Game.h"
#include "Exceptions.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"

namespace mtm
{


    Game::Game(int height, int width) : height(height > 0 ? 0 : throw mtm::IllegalArgument()),
                                            width(width > 0 ? 0 : throw mtm::IllegalArgument()),
                            gameboard( std::vector<std::shared_ptr<Character>>( (height*width) ) )
    {
        // if (height <= 0 || width <= 0)
        // {
        //     throw IllegalArgument();
        // }
        // is it better to throw the exception at initialization list?
    }
    
    Game::~Game()
    {
        //make sure to go over the entire gameboard, i.e the vector and deallocate the memory in each shared_ptr
        // for (std::shared_ptr<Character> i : gameboard)
        // {
        //     // std::vector<std::shared_ptr<Character>>::iterator to_free = i;
        //     // since we have a shared_ptr we probably can just put nullptr in it's place and the count will reach 0
        //     // resulting in the deallocating the characters!
        //     (i) = nullptr;//correct implementation?
        // }
        //if I understood correctly, the destructor of vector destroys our shared_ptrs, assuming
        // that they're only stored there!
    }



    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {
        //we have already created the character and we only have to add the coordinates! and add it to the gameboard
        for ( std::shared_ptr<Character> i : gameboard)
        {
            if ( i == nullptr)
            {
                i = character;//correct implementation?
            }   
        }
        character->coordinates = coordinates;
        return;
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team, 
                            units_t health, units_t ammo, units_t range, units_t power)
    {
        switch (type)
        {
        case SOLDIER:
            return(std::shared_ptr<Soldier>(new mtm::Soldier(health,ammo,power,range,team)));
            break;
        case MEDIC:
            return(std::shared_ptr<Medic>(new mtm::Medic(health,ammo,power,range,team)));
            break;
        case SNIPER:
            return(std::shared_ptr<Sniper>(new mtm::Sniper(health,ammo,power,range,team)));
            break;            
        default:
            break;
        }
        //should never get here, but added this extra return just so that I DON'T GET A WARNING
        return nullptr;
    }


    void Game::move(const GridPoint & src_coordinates,  const GridPoint & dst_coordinates)
    {
        if (isCellOcupied(dst_coordinates) == true)
        {
            throw CellOccupied();
            return;
        }
        for (std::shared_ptr<Character> i : gameboard)
        {
            if ( (i)->coordinates == src_coordinates)
            {
                if ((i)->isMovingDistanceLegal(src_coordinates,dst_coordinates) == true)//correct implementation?
                {
                    (i)->coordinates = dst_coordinates;
                    return;
                }
                else
                {
                    //otherwise it means that he's trying to move a distance larger than range!
                    throw MoveTooFar();
                    return;
                }
            }
        }
        //if we are here it means that we didn't find any characters at src_coordinates, threfore:
        throw CellEmpty();
        return;
    }

    void Game::reload(const GridPoint & coordinates)
    {
        for ( std::shared_ptr<Character> i : gameboard)
        {
            if ( (i)->coordinates == coordinates)
            {
                (i)->reload();//correct implementation?
            }
        }
    }

    bool Game::isCellOcupied(const GridPoint &dst_coordinates)
    {
        for (std::shared_ptr<Character> i : gameboard)
        {
            if ( (i)->coordinates == dst_coordinates )
            {
                return true;
            }
        }
        return false;         
    }

    // a function that resturn a pointer to the character that's at dst_coordinates, otherwise it returns nullptr
    std::shared_ptr<Character> Game::findCharacterAtCoordinates(const GridPoint &dst_coordinates)
    {
        for(std::shared_ptr<Character> i : gameboard)
        {
            if ( i->coordinates == dst_coordinates )
            {
                return (i);
            }
        }
        return (nullptr);
    }

        bool Game::isCellOnGameBoard(const GridPoint &coordinates)
    {
        if ( (coordinates.row < height) && (coordinates.row >= 0) )
        {
            if ( (coordinates.col < width) && (coordinates.col >= 0) )
            {
                return true;
            } 
        }
        return false;
    }

    void Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
    {
        //need to kill some of those lines, make a function for checking errors!
        if (this->isCellOnGameBoard(src_coordinates) == false ||
                 this->isCellOnGameBoard(dst_coordinates) == false )
        {
            throw mtm::IllegalCell();
        }
        std::shared_ptr<Character> attacker = this->findCharacterAtCoordinates(src_coordinates);
        if (attacker == nullptr)
        {
            throw mtm::CellEmpty();
        }
        if (GridPoint::distance(src_coordinates,dst_coordinates) > attacker->range)
        {
            throw OutOfRange();
        }
        if (attacker->ammo <= 0)
        {
            throw OutOfAmmo();
        }        
        std::shared_ptr<Character> main_target = this->findCharacterAtCoordinates(dst_coordinates);
        bool *can_reduce_ammo = nullptr;// check what it's initialized to
        for (std::shared_ptr<Character> i : gameboard)
        {
            attacker->attack( i , main_target,src_coordinates , dst_coordinates,can_reduce_ammo);//we launched the attack, May The Almighty Have Mercy Upon Us :P 
        }
        //make sure to update the ammo and the gameboard after launching an attack, AKA remove any player whose health reached 0
        updaterPlayerAfterAnAttack(gameboard);
        if ( (can_reduce_ammo != nullptr) && (*can_reduce_ammo == true) )
        {
         //does the pointer makes problems?
            Character::decrementAmmoAfterAttack(attacker);
        }
        //we have a problem, we don't always need to decrement the ammo after an attack as it is problematic with medic!
        return;
    }

    void Game::updaterPlayerAfterAnAttack(std::vector<std::shared_ptr<Character>> gameboard)
    {
        for ( std::shared_ptr<Character> i : gameboard)
        {
            if ( (i->health) <= 0)
            {
                i = nullptr;
            }
            
        }
        
    }

    bool Game::isOver(Team* winningTeam) const
    {
        bool found_player_from_cf = false;
        bool found_player_from_pl = false;
        for (std::shared_ptr<Character> i : gameboard)
        {
            //could be a bit problematic in case there are no players from either team on the gameboard!
            if ( (i)->team == CROSSFITTERS )
            {
                found_player_from_cf = true;
            }
            if ( (i)->team == POWERLIFTERS )
            {
                found_player_from_pl = true;
            }
        } 
        bool result = ( ! (found_player_from_cf && found_player_from_pl) );
        if (result == true)
        {
            if (found_player_from_cf == true)
            {
                *winningTeam = CROSSFITTERS;
            }
            if (found_player_from_pl == true)
            {
                *winningTeam = POWERLIFTERS;
            }
        }
        return result;        
    }

    std::ostream& operator<<(std::ostream& os,  const char* begin, const char* end,
                            unsigned int width, std::vector<std::vector<char>> board)
    {

    }
};