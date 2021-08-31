
#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <iostream>
using std::string;
using std::endl;


namespace mtm
{ 
    class Exception : public std::exception
    {
        private:
        string error_message;
        
        protected:
        explicit Exception(const string& name);
        ~Exception()=default;
        
        public:
        virtual const char* what() const noexcept;
    };
    
    class IllegalArgument : public Exception
    {
        public:
        IllegalArgument();
    };

    class IllegalCell  : public Exception
    {
        public:
        IllegalCell();
    };

    class CellEmpty  : public Exception
    {
        public:
        CellEmpty();
    };

    class MoveTooFar : public Exception
    {
        public:
        MoveTooFar();
    };

    class CellOccupied  : public Exception
    {
        public:
        CellOccupied();
    };

    class OutOfRange  : public Exception
    {
        public:
        OutOfRange();
    };

    class OutOfAmmo : public Exception
    {
        public:
        OutOfAmmo();
    };

    class IllegalTarget : public Exception
    {
        public:
        IllegalTarget();
    };
};

#endif