#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "ex3.h"
using namespace std;


/*

string trim(const string& str)
{
   size_t first = str.find_first_not_of("\t\n\v\f\r ");
   if (string::npos == first)
   {
       return str;
   }
   size_t last = str.find_last_not_of("\t\n\v\f\r ");
   return str.substr(first, (last - first + 1));
}


vector<string> splitLine(string line, vector<string> splittedStrings ){
   int i=0;
   int j=0;
   string token;
   while(i<line.length()){
       if (line[i]=='"'){
           j=i+1;
           while(j<line.length()){
               if (line[j]=='\"') {
                   token = line.substr(0,j+1);
                   splittedStrings.push_back(trim(token));
                   line = trim(line.erase(0, j+1));
               }
               j++;
           }
           if (!(line[0]==',')){
               break;
           }
       }else if (line[i]==' '){
           token = line.substr(0, line.find(' '));
           splittedStrings.push_back(trim(token));
           line = trim(line.erase(0, line.find(' ')+1));
           i=0;
       }else if (line[i]=='('){
           token = line.substr(0, line.find('('));
           splittedStrings.push_back(trim(token));
           line = trim(line.erase(0, line.find('(')+1));
           i=0;
       }else if(line[i]==')'){
           token = line.substr(0, line.find(')'));
           splittedStrings.push_back(trim(token));
           line = trim(line.erase(0, line.find(')')+1));
           i=0;
       }else if (line[i] == ','){
           if (!(line[0]==',')){
               token = line.substr(0, line.find(','));
               splittedStrings.push_back(trim(token));
           }

           line = trim(line.erase(0, line.find(',')+1));
           i=0;
       }else if (((line[i]=='<')||(line[i]=='>'))&&(line[i+1]=='=')){
           //token = line.substr(0, line.find('<'));
           if (line[i]=='<'){
               splittedStrings.push_back("<=");
               line =trim(line.erase(0, line.find('<')+2));
           }else{
               splittedStrings.push_back(">=");
               line =trim(line.erase(0, line.find('>')+2));
           }
           i=0;
       }
       else if (line[i]=='=') {
           splittedStrings.push_back("=");
           token = line.substr(line.find('=')+1);
           splittedStrings.push_back(trim(token));
           break;
       }else if (line[i]=='{'){
           splittedStrings.push_back("{");
           break;
       }else if (line[i]=='}'){
           splittedStrings.push_back("}");
           break;
       } else{
           i++;
       }
   }
   return splittedStrings;
}

vector<string> lexer(char* fileName){
   fstream file (fileName, ios::in);
   if(!file){
       //couldn't open the file.
       throw "error with file";
   }else {
       //vector for all words in file
       vector<string> splittedStrings;
       string line{};
       while (!file.eof()){
           getline(file, line);
           //split the line to words
           splittedStrings = splitLine(line, splittedStrings);
       }
       return splittedStrings;
   }
}









void parser (vector<string> splittedStrings){

//    commandMap <string,

}
 */


int main(int argc, char *argv[]) {
   try{
       Ex3 ex3;
       vector<string> splittedStrings = ex3.lexer(argv[1]);
/*
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

