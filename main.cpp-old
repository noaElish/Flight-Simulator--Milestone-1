#include <iostream>
#include <string>
#include <vector>
#include "ex3.h"
using namespace std;



int main(int argc, char *argv[]) {
   try{
       Ex3 ex3;
       vector<string> splittedStrings = ex3.lexer(argv[1]);
/*
        //print the vector
       for (vector<string>::const_iterator iter = splittedStrings.begin(); iter != splittedStrings.end(); ++iter){     //delete
           cout << *iter << endl;
       }
*/
       ex3.parser (splittedStrings);

   }catch(const char* e){
       cout << e << endl;
   }
   return 0;
}

