#include "Game.h"
#include "Exceptions.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"

namespace mtm
{


    Game::Game(int height, int width) : height(height),width(width),
            gameboard( height,(std::vector<std::shared_ptr<Character>>(width,nullptr) )  )
    {
        if (height <= 0 || width <= 0)
        {
            throw IllegalArgument();//correct implementation or is it better to do this at initialization list
        }
    }
    
    Game::~Game()
    {

    }



    void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
    {
        if (isCellOnGameBoard(coordinates) == false)
        {
            throw IllegalCell();
        }
        std::shared_ptr<Character> character_at_wanted_dst = findCharacterAtCoordinates(coordinates);
        if (character_at_wanted_dst != nullptr)
        {
            throw CellOccupied();
        }
        character->coordinates = coordinates;//update the character's location!
        for ( int i = 0; i < this->height; i++)
        {
            for ( int j = 0; j < this->width; j++ )
            {
                GridPoint point = GridPoint(i,j);
                if ( point == coordinates)
                {
                    this->gameboard[i][j] = character;//correct implementation?
                }              
            } 
        }
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
        if( !(isCellOnGameBoard(src_coordinates) && isCellOnGameBoard(dst_coordinates)) )
        {
            throw IllegalCell();
        }
        std::shared_ptr<Character> to_be_moved = findCharacterAtCoordinates(src_coordinates);
        if (to_be_moved == nullptr)
        {
            throw CellEmpty();
        }
        
        Character& character_to_be_moved = *to_be_moved;
        if (character_to_be_moved.isMovingDistanceLegal(src_coordinates,dst_coordinates) == false)
        {
            throw MoveTooFar();
        }
        
        std::shared_ptr<Character> move_to = findCharacterAtCoordinates(dst_coordinates);
        if (move_to != nullptr)
        {
            throw CellOccupied();
        }
        //if we got to this point, it means that we're allowed to move this character!
        to_be_moved->coordinates = dst_coordinates;
        this->gameboard[src_coordinates.row][src_coordinates.col] = nullptr;
        this->gameboard[dst_coordinates.row][dst_coordinates.col] = to_be_moved;
        return;
    }

    void Game::reload(const GridPoint & coordinates)
    {
        if(isCellOnGameBoard(coordinates) == false)
        {
            throw IllegalCell();
        }
        std::shared_ptr<Character> targeted_reload = findCharacterAtCoordinates(coordinates);
        if (targeted_reload == nullptr)
        {
            throw CellEmpty();
        }
        targeted_reload->reload();
        return;
    }

    bool Game::isCellOcupied(const GridPoint &dst_coordinates)
    {
        std::shared_ptr<Character> wanted = findCharacterAtCoordinates(dst_coordinates);
        if (wanted == nullptr)
        {
            return false;
        }
        return true;         
    }

    // a function that resturn a pointer to the character that's at dst_coordinates, otherwise it returns nullptr
    std::shared_ptr<Character> Game::findCharacterAtCoordinates(const GridPoint &dst_coordinates)
    {
        // for ( std::vector<std::shared_ptr<Character>> row_vectors : gameboard)
        // {
        //     for (std::shared_ptr<Character> i : row_vectors)
        //     {
        //         if ( i->coordinates == dst_coordinates )
        //         {
        //             return (i);
        //         }              
        //     } 
        // }
        // return (nullptr);
        for(int i = 0; i < this->height; i++)
        {
            for(int j = 0; j < this->width; j++)
            {
                GridPoint point = GridPoint(i,j);
                if ( point == dst_coordinates )
                {
                    return(this->gameboard[i][j]);
                }
            }
        }
        return (nullptr);
    }

    bool Game::isCellOnGameBoard(const GridPoint &coordinates)
    {
        if ( (coordinates.row < this->height ) && (coordinates.row >= 0) )
        {
            if ( (coordinates.col < this->width) && (coordinates.col >= 0) )
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
        std::shared_ptr<Character> main_target = this->findCharacterAtCoordinates(dst_coordinates);
        for (int i = 0; i < this->height; i++)
        {
            bool can_keep_attacking = false;//pass it as reference below!
            for (int j = 0; j < this->width; j++)
            {
                attacker->attack( gameboard[i][j],main_target,src_coordinates,dst_coordinates,can_keep_attacking); 
                this->removeDeadPlayers();
                if ( can_keep_attacking == false )
                {
                    break;
                } 
            }
            if ( can_keep_attacking == false )
            {
                break;
            }
        }
        return;
    }

    void Game::removeDeadPlayers()
    {
        for ( int i = 0; i< this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {
                if ( (this->gameboard[i][j] != nullptr) && 
                    ( (this->gameboard[i][j]->health) <= 0 ) ) 
                {
                    this->gameboard[i][j] = nullptr;
                }
            }
        }
        return;   
    }

    bool Game::isOver(Team* winningTeam) const
    {
        bool found_player_from_cf = false;
        bool found_player_from_pl = false;
        for (std::vector<std::shared_ptr<Character>> row_vectors : gameboard)
        {
            for (std::shared_ptr<Character> i : row_vectors)
            {
                if ( (i != nullptr) && (i)->team == CROSSFITTERS )
                {
                    found_player_from_cf = true;
                }
                if ( (i != nullptr) && (i)->team == POWERLIFTERS )
                {
                    found_player_from_pl = true;
                }
            }
        } 
        if ( (found_player_from_cf == true && found_player_from_pl == false) ||
                         (found_player_from_cf == false && found_player_from_pl == true) )
        {
            if (found_player_from_cf == true)
            {
                *winningTeam = CROSSFITTERS;
            }
            if (found_player_from_pl == true)
            {
                *winningTeam = POWERLIFTERS;
            }
            return true;
        }
        //else there are players from both teams or player from only one team!
        return false;           
    }

    Game::Game(const Game &other) : height(other.height), width(other.width),
                    gameboard(other.height,std::vector<std::shared_ptr<Character>>(other.width,nullptr))
    {
        for(int i = 0; i <other.height; i++)
        {
            for(int j = 0; j < other.width; j++)
            {
                if ( (other.gameboard[i][j]) == nullptr )
                {
                    this->gameboard[i][j] = nullptr;
                }
                else
                {
                    this->gameboard[i][j] = (other.gameboard[i][j])->clone();
                }
            }
        }
        this->height = other.height;
        this->width = other.width;
    }

    Game& Game::operator=(const Game &other)
    {
        this->width = other.width;
        this->height = other.height;
        for(int i = 0; i < other.height; i++)
        {
            for(int j = 0; j < other.width; j++)
            {
                if ( (other.gameboard[i][j]) == nullptr )
                {
                    this->gameboard[i][j] = nullptr;
                }
                else
                {
                    this->gameboard[i][j] = (other.gameboard[i][j])->clone();
                }
            }
        }
        return (*this);
    }

    std::ostream& operator<<(std::ostream& os, const Game& game)                               
    {
        const string EMPTY_SPACE = " ";//correct implementation?
        std::string gameboard_as_a_string;
        for (int i = 0; i < game.height; i++)
        {
            for (int j = 0; j < game.width; j++)
            {
                if (game.gameboard[i][j] == nullptr)
                {
                    gameboard_as_a_string += EMPTY_SPACE;
                }
                else
                {
                    gameboard_as_a_string += (game.gameboard[i][j])->fillCharacterSymbol();
                }
            }
        }
        int len=gameboard_as_a_string.length();
        // char* grid_char_to_print=new char[grid_as_string_len+1]; 
        // strcpy(grid_char_to_print,gameboard_as_a_string);
        printGameBoard(os,(&gameboard_as_a_string[0]),(&gameboard_as_a_string[len]),game.width);
        // delete[] grid_char_to_print;      
        return os;
    }
}