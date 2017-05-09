#include "Base.h"
#ifndef AND_H
#define AND_H

class And: public Base{
    Base* Left;
    Base* Right;
    
    public:
    And(){};
    
    
    //named it l and r( the base pointer)
    And(Base*, Base*);
    // implement so that it calls the left excutes first then the right depends on the left's execution look at
    // at the manual for the assighment.
    virtual bool execute();
};
#endif