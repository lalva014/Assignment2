#include <iostream>
#include <sstream>      // std::stringstream
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Base.h"
#include "Semi.h"
#include "Command.h"
#include "And.h"
#include "Or.h"


using namespace std;

char * conToCommand(vector<string> line){
    int arraySize = line.size() + 1;
    char *array =  (char*)malloc(arraySize);
    for(unsigned i = 0; i + 1 < line.size(); i++){
        strcpy(array, line.at(i).c_str());
    }
    array[arraySize - 1] = 0;
    return array;

}

// it converts a string into an array of char
char * Convert(string line){
    char *array =  (char*)malloc(line.size());
    strcpy(array, line.c_str());
    return array;

} 
vector <char *> conArg(char * point, int num){
    char* p = strtok(point, " ");
    vector<char*> ar;
    ar.push_back(p);
    p = strtok(NULL, " ");
    int i = 0;
    while(p != NULL){
        ar.push_back(p);
        p = strtok(NULL, " ");
        ++i;
    }
    
    return ar;
}

void execute(vector<Base*> B){
      for(unsigned i = 0; i < B.size(); i++){
      pid_t pid = fork();
        
        //child running 
        if (pid == 0){
                ( B.at(i) )->execute();
        } /// parent running
        else if (pid > 0){
            wait(NULL);
            
         
        }
        else
        {
            // fork failed
            cout << "Fork fails \n";
            exit(-1);
        }
      }
}

int sizeChar(char * pointer){
    pointer  = strtok(pointer, " ");
    int size = 0;
    size++;
    while(pointer != NULL){
         pointer  = strtok(NULL, " ");
         size++;
    }
    return size;
}

// are we going to call the ex function in the BuiltTree?? no we call the vector of basses inside of ex. built tree returns the top of the tree.
//how come builtTree is not a class itself and inherits from base ?? nvm why ????
Base * BuiltTree(string line){
    string l = line;
    char * pointer= Convert(line);
    stringstream broken;
    broken << l;
    string single;
    vector<string> v;
    bool start =  false;
    vector<Base*> VB;

    while(broken >> single){
        if(single == "&&"){
            if(false == start){
                Command * c1 = new Command(v);
                pointer = strtok(pointer,"&|");
                pointer = strtok(NULL, "&|");
                string loc(pointer);
                stringstream nextCom(loc);
                string x;
                vector<string> nol;
                while(nextCom >> x){
                    nol.push_back(x);
                }
                Command * c2 = new Command(nol);
                And * n = new And(c1, c2);
                VB.push_back(n);
                start = true;
            }
            else{
                pointer = strtok(NULL, "|&");
                string p(pointer);
                stringstream f(p);
                string co;
                vector<string> w;

                while(f >> co ){
                    w.push_back(co);
                }
                Command* c = new Command(w);
                Base* temp = new And(VB.at(0), c);
                VB.at(0) = temp;
            }
            
        }
        else if(single == "||"){
         
            if(false == start){
                Command * c1 = new Command(v);
                pointer = strtok(pointer,"&|");
                pointer = strtok(NULL, "&|");
                string loc(pointer);
                stringstream nextCom(loc);
                string x;
                vector<string> nol;
                while(nextCom >> x){
                    // cout <<  x << " "
                    nol.push_back(x);
                }
                // cout << "end of or command" endl;
                Command * c2 = new Command(nol);
                Or * n = new Or(c1, c2);
                VB.push_back(n);

                start = true;
            }
            else{
                 pointer = strtok(NULL, "|&");
                string p(pointer);
                stringstream f(p);
                string co;
                vector<string> w;
                while(f >> co ){
                    w.push_back(co);
                }
                Command* c = new Command(w);
                Base* temp = new Or(VB.at(0), c);
                VB.at(0) = temp;
            }    
        }
        v.push_back(single);
    }
  return VB.at(0); 
}


vector<string> split(char* l){
    vector<string> v;
    char *pointer  = strtok(l,";");
    string p(pointer);
     v.push_back(p);
    pointer  = strtok(NULL,";");
        while(pointer != 0){
            string s(pointer);
            s.erase(0,1);
            v.push_back(s);
            pointer  = strtok(NULL,";");
 
        }
    return v;
} 
 bool checkQuit(string line){
    string w;
    stringstream word; // stream word 
    word.str(""); // clearingthe stream of word
    word.clear();   // more clearing
    word << line;   // dumps the content of line into word.
    while (word >> w){   // line is a sentence so when it word does this to a string it only outputs word by word.
        if(w == "Quit"){
            return true;
        }
        if(w == "quit"){
            return true;
        }
    }
    return false;
 }
 
void semi(vector<string>& commands, vector<Base*> &b){

    vector<int> num; 
    if(commands.size() == 1){
            char * pointer = Convert(commands.at(0));
            pointer = strtok(pointer, "&|");
            string check(pointer);
            if(check == commands.at(0)){
        
                vector<string>v;
                stringstream p(commands.at(0));
                string single;
                while(p >> single){
                    v.push_back(single);
                }
                Base * s = new Semi(v);
                b.at(0) = s;
                commands.at(0) = "";
                num.push_back(0);
            }
    }
    else{
        char * f = Convert(commands.at(0));
        f = strtok(f, "|&");
        string test(f);
        
            if(test == commands.at(0)){
                vector<string>v;
                stringstream p(commands.at(0));
                string single;
                while(p >> single){
                    v.push_back(single);
                }
                Base * sv = new Semi(v);
                b.at(0)= sv;
                commands.at(0) = "";
                num.push_back(0);
            
        }
        unsigned i = 1;
        char * w = Convert(commands.at(i));
        char * point = strtok(w, "|&");
        while(point != NULL){
                string t(point);
                if(t == commands.at(i) ){
                    vector<string>v;
                    stringstream w(commands.at(i));
                    string single;
                    while(w >> single){
                        v.push_back(single);
                    }
                    Base * s = new Semi(v);
                    b.at(i)= s;
                    commands.at(i) = "";
                    num.push_back(i);
                }
                if(commands.size() == i + 1){
                    break;
                }
                i++;
                w = Convert(commands.at(i));
                point = strtok(w, "|&");

            
            }
    
        
    }
    

    

    
 }
 vector<Base*> Tree( vector <Base*>& b,vector<string> v ){
        vector<string> s;
        Base* pointer;
        for(unsigned i = 0;  i < v.size(); i++ ){
            if(v.at(i) != ""){
                pointer = BuiltTree( v.at(i) );               // we call that function
                b.at(i) =pointer;
            }
        }
        return b;
        

 }
 string checkComment(string line){
    char * pointer =Convert(line);
    pointer = strtok(pointer, "#");
    string newLine(pointer);
    return newLine;
    
 }
 
 
 
// where we run the loop
void command(){
    vector<string> v;
    vector <Base*> b;
    vector <string> cn;
    while(true){
        cout << "$ ";
        string line;
        getline(cin,line); // gets the commands 
        line = checkComment(line); // ignores everything after the #
        if( checkQuit(line) ) break; /// checks if the word Quit is in them. if so exits the shell
        char *l = Convert(line); // converts the string line to a char* 
        v = split(l);   // it return a vector of char* each of them is a command follow by its paramaters;
        b.resize(v.size()); // the number of base in the vector.
        semi(v,b);// returns all of the commands are executed right away in a vector of bases; cn is commands
    
    
            b = Tree(b,v);
        
        execute(b);
        
    }       
    
}

int main(){
    command();
//   vector<string> v;
//   v.push_back("l");
//   vector<string> t;
//   vector<string> w;
//   w.push_back("cho");
//   w.push_back("bye");
  
//   vector<string> py;
//   py.push_back("ls");
 
//   t.push_back("echo");
//   t.push_back("execute");
//      Command* c3 = new Command(t);
//     Command* c1 = new Command(v);
//     Command* c2 = new Command(w);
//     Command* c4 = new Command(py);

//     Or* one =  new Or(c1,c2);
//     Or* two = new Or(one,c3);
//     Or* thr = new Or(two, c4);
//     cout << "the resutl of the boolen " << thr->execute() << endl;
//     two->execute();
    
    return 0;
}