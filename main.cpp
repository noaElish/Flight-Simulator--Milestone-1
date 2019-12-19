#include <iostream>
#include <string>
#include <vector>
#include "cmake-build-debug/CMakeFiles/Interpreter.h"

using namespace std;



int main(int argc, char *argv[]) {
    try{
        Interpreter inter;
        vector<string> splittedStrings = inter.lexer(argv[1]);
/*
        //print the vector
       for (vector<string>::const_iterator iter = splittedStrings.begin(); iter != splittedStrings.end(); ++iter){     //delete
           cout << *iter << endl;
       }
*/
        inter.parser (splittedStrings);

    }catch(const char* e){
        cout << e << endl;
    }
    return 0;
}

