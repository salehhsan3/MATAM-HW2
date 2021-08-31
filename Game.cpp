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
        for (std::vector<std::shared_ptr<Character>>::iterator i = gameboard.begin(); i != gameboard.end(); i++)
        {
            // std::vector<std::shared_ptr<Character>>::iterator to_free = i;
            // since we have a shared_ptr we probably can just put nullptr in it's place and the count will reach 0
            // resulting in the deallocating the characters!
            (*i) = nullptr;//correct implementation?
        }
        
    }



    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {
        //we have already created the character and we only have to add the coordinates!
        (*character).coordinates = coordinates;
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
            return(std::shared_ptr<Medic>(new mtm::Soldier(health,ammo,power,range,team)));
            break;
        case SNIPER:
            return(std::shared_ptr<Sniper>(new mtm::Soldier(health,ammo,power,range,team)));
            break;            
        default:
            break;
        }
    }


    void Game::move(const GridPoint & src_coordinates,  const GridPoint & dst_coordinates)
    {
        if (isCellOcupied(dst_coordinates) == true)
        {
            throw CellOccupied();
            return;
        }
        for (std::vector<std::shared_ptr<Character>>::iterator i = game0board.begin(); i != gameboard.end() ; i++ )
        {
            if ( (*i)->coordinates == src_coordinates)
            {
                // explaination about my implementation of the iterator above :
                // iterators are a generalization of pointers, doing "*" lets me access the object it points at
                // which is a shared_ptr (another pointer) therefore I have to use "->" to derefrence it.
                if ((*i)->isMovingDistanceLegal(src_coordinates,dst_coordinates) == true)//correct implementation?
                {
                    (*i)->coordinates = dst_coordinates;
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
        for ( std::vector<std::shared_ptr<Character>>::iterator i = gameboard.begin(); i != gameboard.end() ; i++)
        {
            if ( (*i)->coordinates == coordinates)
            {
                (*i)->reload();//correct implementation?
            }
        }
    }

    bool Game::isCellOcupied(const GridPoint &dst_coordinates)
    {
        for (std::vector<std::shared_ptr<Character>>::iterator i = gameboard.begin(); i != gameboard.end(); i++)
        {
            if ( (*i)->coordinates == dst_coordinates )
            {
                return true;
            }
        }
        return false;         
    }

    // a function that resturn a pointer to the character that's at dst_coordinates, otherwise it returns nullptr
    std::shared_ptr<Character> Game::findCharacterAtCoordinates(const GridPoint &dst_coordinates)
    {
        for(std::vector<std::shared_ptr<Character>>::iterator i = gameboard.begin(); i != gameboard.end(); i++)
        {
            if ((*i)->coordinates == dst_coordinates)
            {
                return (*i);
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
        // notice that (this) in the following context is Game,even though adding it 
        // isn't required, it helps in understanding the code better therefore I added it!
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
            // a little explanation : I would prefer to check for the legality of the distance here
            // because then it lets me iterate over the contents of vector and "try to" attack each of them
            // independently, meaning I wouldn't throw OutOfRange() in case of distance problems :P 
            throw OutOfRange();
        }
        //std::shared_ptr<Character> attacked = findCharacterAtCoordinates(dst_coordinates);
        // the attacked pointer is probably not needed!
        
        for ( std::vector<std::shared_ptr<Character>>::iterator i = this->gameboard.begin();
                                                             i != this->gameboard.end(); i++)
        {
            attacker->attack( (*i) , src_coordinates , dst_coordinates);//we launched the attack, May The Almighty Have Mercy Upon Us :P 
        }
        
        //make sure to update the gameboard after launching an attack, AKA remove any player whose health reached 0
        return;
    }

    bool Game::isOver(Team* winningTeam) const
    {
        bool found_player_from_cf = false;
        bool found_player_from_pl = false;
        for (std::vector<std::shared_ptr<Character>>::iterator i = this->gameboard.begin();
                                                ( i != this->gameboard.end() ); i++)
        {
            //could be a bit problematic in case there are no players from either team on the gameboard!
            if ( (*i)->team == CROSSFITTERS )
            {
                found_player_from_cf = true;
            }
            if ( (*i)->team == POWERLIFTERS )
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
};