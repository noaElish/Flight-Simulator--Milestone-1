

#include "Command.h"
#include "Interpreter.h"
#include "Expression.h"
#include "ex1.h"
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <regex>
#include <sstream>
using namespace std;

Interpreter inter;

//function of open Command
void openDataServer(int port) {
    //creating new socket
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer == -1) {
        //cant create socket
        std::cerr << "cant create socket" << std::endl;
    }
    //create the object for the bind
    sockaddr_in addressSer;
    addressSer.sin_family = AF_INET;
    addressSer.sin_addr.s_addr = INADDR_ANY;
    addressSer.sin_port = htons(port);

    //bind the socket to ip
    int binding = bind(socketServer, (struct sockaddr *) &addressSer, sizeof(addressSer));
    if (binding == -1) {
        std::cerr << "cant bind socket to ip" << std::endl;
    }

    //listen to the port
    int listenning = listen(socketServer, 5);
    if (listenning == -1) {
        std::cerr << "cant listen to ip" << std::endl;
    }




    int acc = accept(socketServer, (struct sockaddr *)&addressSer, (socklen_t *)&addressSer);

    //accept the client- flight gear
    //int clientSock = accept(socketServer, (struct sockaddr *) &addressSer, (socklen_t *) &addressSer);
    if (acc == -1) {
        std::cerr << "cant accept client" << std::endl;
    }


    //reading from the socket line by line-use loop-CHECK/////////////////

    //save each line to the data structure
    char bufferRead[1024] = {0};
    int value;
    SymbolTable* instance = SymbolTable::getInstance();
    size_t i=0;
    string token;
    string s;
    float num;
    int index=0;
    while(true){
        value = read(acc, bufferRead, 1024);
        if (value == -1) {
            std::cerr << "error with read" << std::endl;
        }
        while (i< sizeof(bufferRead)){

            s = s + bufferRead[i];
            if ((bufferRead[i]==',')){
                token = s.substr(0, s.find(','));
                num = stof(token);
                instance->putInSimMap(index, num);
                s = s.erase(0, s.find(',')+1);
                index++;
                //cout<<"token:  "<<token<<"   num:  "<<num<<"  index:  "<<index<<endl;
            }
            if ((bufferRead[i]=='\0')){
                token = s.substr(0, s.find('\0'));
                num = stof(token);
                instance->putInSimMap(index, num);
                s = s.erase(0, s.find('\0')+1);
                index=0;
                //cout<<"token:  "<<token<<"   num:  "<<num<<"  index:  "<<index<<endl;
                break;
            }
            i++;
        }
        i=0;

    }
    //closing the socket
    close(socketServer);
}


/**
 * Class for OpenServerCommand
 */
//constructor
OpenServerCommand::OpenServerCommand() {};
int OpenServerCommand::execute(vector<string> arrayStr, int i) {
    cout << "in open server" << endl;
    port = stoi(arrayStr[i + 1]);
    //open thread to to connect
    thread threadServer(openDataServer, port);
    threadServer.join();
    return 2;
};
//destructor
OpenServerCommand::~OpenServerCommand() {};

/**
 * Class for ConnectCommand
 */
ConnectCommand::ConnectCommand() {};

//function of connect Command
void connectControlClient(string adressConnect, int port) {

    //create new socket
    int socketClient = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketClient == -1) {
        std::cerr << "cant create socket" << std::endl;
    }

    //create the object for the bind
    sockaddr_in addressSer;
    addressSer.sin_family = AF_INET;
    addressSer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addressSer.sin_port = htons(port);

    int connectUs = connect(socketClient, (struct sockaddr *) &addressSer, sizeof(addressSer));
    //check if connected
    if (connectUs == -1) {
        std::cerr << "cant create socket" << std::endl;
    } else {
        std::cerr << "connected to server" << std::endl;
    }
}

int ConnectCommand::execute(vector<string> arrayStr, int i) {
    cout << "in connect command" << endl;

    adress = arrayStr[i + 1];
    port = stoi(arrayStr[i + 2]);
    std::thread threadClient(connectControlClient, adress, port);
    threadClient.join();
    return 4;
}
//destructor
ConnectCommand::~ConnectCommand() {};


/**
 * Class for DefineVarCommand
 */
//constructor
DefineVarCommand::DefineVarCommand(){};
int DefineVarCommand::execute(vector<string> arrayStr, int i) {
    /*
    float value = 3;
    string sim = "p";
    string direction = "o";
    SymbolTable *symbolsMaps = symbolsMaps->getInstance();
    Variable variable = new Variable(value,sim, direction);
   // v= new Variable(3, "h", "o");
    string d= "hh";
    //symbolsMaps->symbolTable.insert(d, var);
    symbolsMaps->putInSymbolTable(d,variable);
    */

    cout << "in var def" << endl;
    /**need to change this func**///////////////////////////////////////////////////////////////////////
    index = i;

    SymbolTable *instance = instance->getInstance();

    string saveName = arrayStr[i];
    //send the string after the "=" to expression
    Inter *i1 = new Inter();
    Expression *next;
    next = i1->interpret(arrayStr[i + 2]);
    double value = next->calculate();

    //check the direction
    Variable check = instance->symbolTable.at(arrayStr[i]);
    string dir = check.getDir();

    //update the value in the first map
    if (dir == "->") {
        //change the value in the symbol table
        //erase the old one
        Variable check = instance->symbolTable.at(arrayStr[i]);
        string sim = check.getSim();
        instance->symbolTable.erase(arrayStr[i]);
        //create new value
        Variable* insert= new Variable(stoi(arrayStr[i+2]), sim, dir);
        string name= arrayStr[i];
        instance->symbolTable.insert({name,*insert});
        //change the value in the sim table
        instance->simMap.erase(sim);
        instance->simMap.insert({sim,value});

    } else if (dir == "<-") {
        //save the value from the sim table
        float saveValue= instance->getValueFromSim(arrayStr[i+2]);
        //save it to the symbol table
        Variable* insert= new Variable(saveValue, arrayStr[i+2], dir);
        instance->symbolTable.erase(arrayStr[i]);
        string name= arrayStr[i];
        instance->symbolTable.insert({name,*insert});
    }


    /*if (arrayStr[index + 1].compare("=") == 0) {
      return 2;
    } else if ((arrayStr[index + 1].compare("while")) || (arrayStr[index + 1].compare("for")) ||
        (arrayStr[index + 1].compare("if"))) {
      return 1;
    } else if ((arrayStr[index + 2].compare("sim") == 0)) {
      return 5;
    } else {
      return 0;
    }*/
}
//destructor
DefineVarCommand::~DefineVarCommand() {};



/**
 * Class for ConditionParser
 */
//constructor
ConditionParser::ConditionParser() {};
//destructor
ConditionParser::~ConditionParser() {};


/**
 * Class for ifCommand
 */
//constructor
ifCommand::ifCommand(int num)
        : index(num) {};
int ifCommand::execute(vector<string> arrayStr, int i) {
    cout << "in if command " << endl;
    return 0;                              //????????????????????
}
//destructor
ifCommand::~ifCommand() {};


/**
 * Class for loopCommand
 */
//constructor
loopCommand::loopCommand(int num) : index(num) {};
int loopCommand::execute(vector<string> arrayStr, int i) {
  //create symbol map
  SymbolTable *symbolsMaps = symbolsMaps->getInstance();
  //create new struct to save the variable name and index in the array
  struct varLoop{
    string nameVr;
    int indexVr;
  };

  int j = index;
  //count the number of num to return
  while (arrayStr[j] != "}") {
    cout << "in while  " << arrayStr[j] << endl;
    j++;
    num++;
  }

  j = index;
  //create new array to hold the variables we want to execute
  varLoop arr[(num - 4) / 3];
  int p = 0;
  //go over the loop again
  while (arrayStr[j] != "}") {
    if (symbolsMaps->symbolTable.find(arrayStr[j]) == symbolsMaps->symbolTable.end()) {
      //not found
    } else {
      //found- save this name to our array - add index number and name
      arr[p].nameVr = arrayStr[j];
      arr[p].indexVr= j;
      p++;
    }
    j++;
  }

  //FOR THE CONDITION
  //save the variable-and its value
  string nameCon = arrayStr[i + 1];
  int nameLoopNum;
  Variable *nameLoopVar = new Variable(0, "", "");
  auto search = symbolsMaps->symbolTable.find(nameCon);
  if (search != symbolsMaps->symbolTable.end()) {
    *nameLoopVar = search->second;
    nameLoopNum = nameLoopVar->getVar();
  }
  //save the sign of the loop
  string signLoop = arrayStr[i + 2];
  //save the number of the loop
  int numberLoop = stoi(arrayStr[i + 3]);

  if (signLoop == "<=") {
    while (nameLoopNum <= numberLoop) {
      for (varLoop k: arr) {
        symbolsMaps->commandMap.find(k.nameVr)->second->execute(arrayStr,k.indexVr);
      }
    }
  }
  if (signLoop == "=>") {
    while (nameLoopNum >= numberLoop) {
      for (varLoop k: arr) {
        symbolsMaps->commandMap.find(k.nameVr)->second->execute(arrayStr,k.indexVr);
      }
    }
  }
  if (signLoop == "<") {
    while (nameLoopNum < numberLoop) {
      for (varLoop k: arr) {
        symbolsMaps->commandMap.find(k.nameVr)->second->execute(arrayStr,k.indexVr);
      }
    }
  }
  if (signLoop == ">") {
    while (nameLoopNum > numberLoop) {
      for (varLoop k: arr) {
        symbolsMaps->commandMap.find(k.nameVr)->second->execute(arrayStr,k.indexVr);
      }
    }
  }
  if (signLoop == "==") {
    while (nameLoopNum == numberLoop) {
      for (varLoop k: arr) {
        symbolsMaps->commandMap.find(k.nameVr)->second->execute(arrayStr,k.indexVr);
      }
    }
  }
  if (signLoop == "!=") {
    while (nameLoopNum != numberLoop) {
      for (varLoop k: arr) {
        symbolsMaps->commandMap.find(k.nameVr)->second->execute(arrayStr,k.indexVr);
      }
    }
  }
  return num;
}
//destructor
loopCommand::~loopCommand() {};


/**
 * Class for Print
 */
//constructor
Print::Print() {};
int Print::execute(vector<string> arrayStr, int i) {
    //print the string
    cout << arrayStr[i + 1] << "_-----" << endl;
    return 2;
}
//destructor
Print::~Print() {};

/**
 * Class for Sleep
 */
//constructor
Sleep::Sleep() {};
int Sleep::execute(vector<string> arrayStr, int i) {
    // sleep(stoi(arrayStr[i+1]));                           //??????????????????????????????
    cout << "sleep  " << stoi(arrayStr[i + 1]) << endl;
    return 2;
}
//destructor
Sleep::~Sleep() {};
