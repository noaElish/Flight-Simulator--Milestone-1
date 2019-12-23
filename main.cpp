#include <iostream>
#include <string>
#include <vector>
#include "Interpreter.h"
using namespace std;
int main(int argc, char *argv[]){
    try{
        Interpreter inter;
        vector<string> splittedStrings = inter.lexer(argv[1]);
        //execute all the commands
        inter.parser (splittedStrings);
    }catch(const char* e){
        cout << e << endl;
    }
    return 0;
}