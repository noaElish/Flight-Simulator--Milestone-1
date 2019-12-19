//
// Created by shira on 19.12.2019.
//

#ifndef EX3PROJECT_COMMAND_H
#define EX3PROJECT_COMMAND_H

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
 * command Interface
 */
class Command {
public:
    virtual int execute(vector<string> arrayStr, int i) = 0;
    //destructor
    virtual ~Command(){};
};


/**
 * Class for OpenServerCommand
 */
class OpenServerCommand : public Command{
protected:
    int port;
public:
    //constructor
    OpenServerCommand();
    int execute(vector<string> arrayStr, int i);
    //destructor
    ~OpenServerCommand();
};


/**
 * Class for ConnectCommand
 */
class ConnectCommand : public Command{
protected:
    string adress;
    int port;
public:
    //constructor
    ConnectCommand();
    int execute(vector<string> arrayStr, int i);
  //  void connectControlClient(string adressConnect, int port);
    //destructor
    ~ConnectCommand();
};

/**
 * Class for DefineVarCommand
 */
class DefineVarCommand : public Command{
private:
    int index;
public:
    DefineVarCommand(int num);
    //DefineVarCommand();  //every class will have a default constructor
    int execute(vector<string> arrayStr, int i);
    //destructor
    ~DefineVarCommand();
};


/**
 * Class for ConditionParser
 */
class ConditionParser : public Command{
public:
    //constructor
    ConditionParser();
    //destructor
    ~ConditionParser();
};


/**
 * Class for ifCommand
 */
class ifCommand : public ConditionParser{
private:
    int index;
public:
    //constructor
    ifCommand(int num);
    int execute(vector<string> arrayStr, int i);
    //destructor
    ~ifCommand();
};


/**
 * Class for loopCommand
 */
class loopCommand : public ConditionParser{
private:
    int index;
    int num;
public:
    //constructor
    loopCommand(int num);
    //loopCommand(){};//every class will have a default constructor
    int execute(vector<string> arrayStr, int i);
    //destructor
    ~loopCommand();
};


/**
 * Class for Print
 */
class Print : public Command{
public:
    //constructor
    Print();
    virtual int execute(vector<string> arrayStr, int i);
    //destructor
    ~Print();
};

/**
 * Class for Sleep
 */
class Sleep : public Command{
public:
    //constructor
    Sleep();
    virtual int execute(vector<string> arrayStr, int i);
    //destructor
    ~Sleep();
};


#endif //EX3PROJECT_COMMAND_H
