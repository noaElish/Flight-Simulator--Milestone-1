//
// Created by shira on 19.12.2019.
//

#ifndef EX3PROJECT_INTERPRETER_H
#define EX3PROJECT_INTERPRETER_H


#include "../Command.h"

#include <thread>
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <unistd.h>
#include <unordered_set>
#include <arpa/inet.h>
using namespace std;



class Interpreter {
public:
    //constructor
    Interpreter();
    //This function deletes unnecessary spaces from words
    string trim(const string& str);
    //This function divides the text into separate words and put them in array
    vector<string> splitLine(string line, vector<string> splittedStrings );
    //This function reads a text from a file and inserts it into an array
    vector<string> lexer(char* fileName);
    //This function builds a map of strings and commands
    map <string, Command*> intoCommandMap(vector<string> splittedStrings,map <string, Command*> commandMap );
    //This function goes on array and executes the commands
    void parser (vector<string> splittedStrings);
    //constructor
    ~Interpreter();
};


#endif //EX3PROJECT_INTERPRETER_H
