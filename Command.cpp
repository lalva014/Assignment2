#include "Command.h"
#include <unistd.h> //library for Fork, execvp, watpid
#include <stdio.h>  //for perror
#include <stdlib.h> // for malloc
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <sys/types.h> 

using namespace std;

//use fork
bool Command::execute()
{
    int status;
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
        //pid_t w;
        //child
         if (pid == 0){
                if( execvp(argc[0], argc)  == -1){ // probably needs to be <0;
                //for an invalid command do we output 
                //"com: command not found" like it is in the terminal except if there is a # in front
                    perror(argc[0]);
                    exit(2);
                }
                
                
              
        } /// parent running
        else if (pid > 0){
            
            wait(&status);
            if(WIFEXITED(status))
            {
                //cout << "hello" << endl;
                if(WEXITSTATUS(status))
                {
                    return false;
                }
                return true;
            }
            
            if(WIFEXITED(status)){
                return false;
            }
            else {
                return true;
            }

         
        }
        else
        {
            // fork failed
            cout << "Fork fails \n";
            exit(-1);
        }

       
        return true;
}
