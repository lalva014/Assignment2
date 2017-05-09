#include "And.h"

#include <unistd.h> //library for Fork, execvp, watpid
#include <stdio.h>  //for perror
#include <stdlib.h> // for malloc
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <sys/types.h> 

using namespace std;

And::And(Base* l, Base* r)
{
    Left = l;
    Right = r;
    
}

bool And::execute(){
        
    if(Left->execute() == true ){
        return  Right->execute();
    }
    else{
        return false;
    }
        
}
