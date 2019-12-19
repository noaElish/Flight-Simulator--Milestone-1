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


void SetArrayOfSim(){
  ArrSim[0]= "/instrumentation/airspeed-indicator/indicated-speed-kt";
  ArrSim[1]="/sim/time/warp";
  ArrSim[2]="/controls/switches/magnetos";
  ArrSim[3]="//instrumentation/heading-indicator/offset-deg";
  ArrSim[4]="/instrumentation/altimeter/indicated-altitude-ft";
  ArrSim[5]="/instrumentation/altimeter/pressure-alt-ft";
  ArrSim[6]="/instrumentation/attitude-indicator/indicated-pitch-deg";
  ArrSim[7]="/instrumentation/attitude-indicator/indicated-roll-deg";
  ArrSim[8]="/instrumentation/attitude-indicator/internal-pitch-deg";
  ArrSim[9]="/instrumentation/attitude-indicator/internal-roll-deg";
  ArrSim[10]="/instrumentation/encoder/indicated-altitude-ft";
  ArrSim[11]="/instrumentation/encoder/pressure-alt-ft";
  ArrSim[12]="/instrumentation/gps/indicated-altitude-ft";
  ArrSim[13]="/instrumentation/gps/indicated-ground-speed-kt";
  ArrSim[14]="/instrumentation/gps/indicated-vertical-speed";
  ArrSim[15]="/instrumentation/heading-indicator/indicated-heading-deg";
  ArrSim[16]="/instrumentation/magnetic-compass/indicated-heading-deg";
  ArrSim[17]="/instrumentation/slip-skid-ball/indicated-slip-skid";
  ArrSim[18]="/instrumentation/turn-indicator/indicated-turn-rate";
  ArrSim[19]="/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
  ArrSim[20]="/controls/flight/aileron";
  ArrSim[21]="/controls/flight/elevator";
  ArrSim[22]="/controls/flight/rudder";
  ArrSim[23]="/controls/flight/flaps";
  ArrSim[24]="/controls/engines/engine/throttle";
  ArrSim[25]="/controls/engines/current-engine/throttle";
  ArrSim[26]="/controls/switches/master-avionics";
  ArrSim[27]="/controls/switches/starter";
  ArrSim[28]="/engines/active-engine/auto-start";
  ArrSim[29]="/controls/flight/speedbrake";
  ArrSim[30]="/sim/model/c172p/brake-parking";
  ArrSim[31]="/controls/engines/engine/primer";
  ArrSim[32]="/controls/engines/current-engine/mixture";
  ArrSim[33]="/controls/switches/master-bat";
  ArrSim[34]="/controls/switches/master-alt";
  ArrSim[35]="/engines/engine/rpm";
}


#endif //EX3PROJECT_COMMAND_H
