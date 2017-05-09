#include "Base.h"
#ifndef SEMI_H
#define SEMI_H
#include <vector>
#include <string>
using namespace std;

class Semi: public Base{
    private:
    vector<string>c;
    
    public:
    Semi(){};
    ~Semi();
    Semi(vector<string> p);
    
    
    //named it l and r( the base pointer)
    // implement so that it calls the left excutes first then the right depends on the left's execution look at
    // at the manual for the assighment.
    virtual bool execute();
};
#endif