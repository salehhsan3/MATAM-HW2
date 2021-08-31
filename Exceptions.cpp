
#include "Exceptions.h"
#include <iostream>
using std::cout;
using std::endl;

namespace mtm
{
    Exception::Exception(const string& name):error_message("A game related error has occurred: " + name){};
    const char* Exception::what() const noexcept
    {
        return error_message.c_str();
    }

    IllegalArgument::IllegalArgument():Exception("IllegalArgument"){}; //why calling inside initialization not inside {}
    IllegalCell::IllegalCell():Exception("IllegalCell"){};
    CellEmpty::CellEmpty():Exception("CellEmpty"){};
    MoveTooFar::MoveTooFar():Exception("MoveTooFar"){};
    CellOccupied::CellOccupied():Exception("CellOccupied"){};
    OutOfRange::OutOfRange():Exception("OutOfRange"){};
    OutOfAmmo::OutOfAmmo():Exception("OutOfAmmo"){};
    IllegalTarget::IllegalTarget():Exception("IllegalTarget"){};



};