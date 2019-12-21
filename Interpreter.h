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


/**
 * Class Interpreter
 */
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




/*
class Variable{

private:
    int value;
    string sim;
    //constructor - It is in the private area so objects cannot be created from outside.

public:
    Variable(int value, string sim);
    //This method allows you to get the pointer to the only object created.
  //  static Variable *getInstance();

    //destructor
    ~Variable();
};
 */

/**
 * Class Variable
 */
class Variable {
private:
    float value;
    string sim;
    string direction;
public:
    //constructor
    Variable(float value, string sim, string direction);
    void updateValue(float num);
    //constructor
    ~Variable();
};


/**
 * Class SymbolTable
 */
class SymbolTable{
private:
    static SymbolTable* instance;
    //constructor - It is in the private area so objects cannot be created from outside.
    SymbolTable();
public:
    map<string, Variable> symbolTable;
    map<string, float > simMap;


    //This method allows you to get the pointer to the only object created.
    static SymbolTable *getInstance();

    void putInSymbolTable(string varName,Variable var);
    void upDateSymbolTable(string,Variable);
    Variable getVariable(string name);
    string SetArrayOfSim(int i);
    void putInSimMap (int i, float num);

    //destructor
    ~SymbolTable();
};


#endif //EX3PROJECT_INTERPRETER_H
