#include "Or.h"
#include "Base.h"
#include <iostream>
using namespace std;

bool Or::execute()
{
    if(Left->execute() ==  false){
        bool temp = Right->execute();
        if(temp == false){
        
            return false;
        }
        else{
            return true;
        }
    }
    else{
        return true;
    }
    
}