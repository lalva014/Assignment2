#include "Semi.h"
#include <stdio.h>  //for perror and exit
#include <stdlib.h> // for malloc
#include <unistd.h> //library for Fork, execvp, watpid
#include <iostream>
#include <string>
#include <string.h>
#include <sys/wait.h>
using namespace std;



Semi::Semi(vector<string> p)
{
    c = p;
}
Semi::~Semi(){
    //delete c;
    // string temp =c.at(0);
    // while(temp)
    // {
    //     temp = c.at(0);                 // i dont think erase calls delete                 
        c.erase( c.begin(),c.end() ); // this should work. the function .end() goes all the way to the last thing in the vector.
    //     // i think a for loop would have been better
    //     delete temp;
    // }
    // for(int i =0; i < c.size; i++)
    // {
    //     delete c.at(i);
    // }
    
    ///how about this ??? i think that deltes the value of the vector and not delallcate the memory it uses

    
}

bool Semi::execute(){
    char **argc =  ( char**)malloc(sizeof(char**)*(c.size()+ 1));
    vector<char*> v;
    for(unsigned int i = 0; i < c.size(); i++){
    string commandss = c.at(i);
    char*array = (char*)malloc(c.at(i).size());
    strcpy(array, commandss.c_str());
    array = strtok(array,"&|");
    v.push_back(array);
            
    }
    for(unsigned int i= 0; i < v.size();i++){
        argc[i] = v.at(i);
    }        
    argc[c.size()] = NULL;
        
    pid_t pid = fork();
    if (pid == 0){
        
        if( execvp(argc[0], argc)  == -1){ // probably needs to be <0;
        perror("exert");
        return false;
        }
        else{
        //delete[] argv;
        return true;
        }
              
    } /// parent running
    else if (pid > 0){
        wait(0);
        return true;
    }
    else
    {
        // fork failed
        cout << "Fork fails \n";
        exit(-1);
    }
        
        
        
        
        

    // if( execvp(argc[0], argc)  == -1){ // probably needs to be <0;
    //     //for an invalid command do we output 
    //     //"com: command not found" like it is in the terminal except if there is a # in front
    //         perror("exert");
    //     return false;
    // }
    // //delete[] argv;
    // return true;
    return true;
}