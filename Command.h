#include <string>
#include <vector>
#include "Base.h"
#ifndef COMMAND_H
#define COMMAND_H 

using namespace std;

class Command: public Base{
    vector<string> c;
    
    public:
    Command(){};
    //~Command();
    // set the left to the left  and right to the right.
    Command(vector<string> c){
        this->c = c;
    };

    // so that it opens it fork with the command. and return if it excuted or not. look at the assignment for more instructions
    virtual bool execute();
};
#endif