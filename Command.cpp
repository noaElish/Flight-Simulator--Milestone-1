//
// Created by shira on 19.12.2019.
//

#include "Command.h"

#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;




//function of open Command
void openDataServer(int port){
    //creating new socket
    int socketServer= socket(AF_INET, SOCK_DGRAM, 0 );
    if (socketServer == -1){
        //cant create socket
        std::cerr <<"cant create socket"<<std::endl;
    }
    //create the object for the bind
    sockaddr_in addressSer;
    addressSer.sin_family= AF_INET;
    addressSer.sin_addr.s_addr= INADDR_ANY;
    addressSer.sin_port= htons(port);

    //bind the socket to ip
    if (bind(socketServer, (struct sockaddr *) &addressSer, sizeof(addressSer))==-1 ){
        std::cerr <<"cant bind socket to ip"<<std::endl;
    }

    //listen to the port
    if (listen(socketServer,5)==-1){
        std::cerr <<"cant listen to ip"<<std::endl;
    }

    //accept the client- flight gear
    if (accept(socketServer, (struct sockaddr*)&addressSer, (socklen_t*)&addressSer)==-1){
        std::cerr <<"cant accept client"<<std::endl;
    }

    //reading from the socket line by line-use loop-CHECK/////////////////
    for (int i = 0; i < 23; i++) {
        //save each line to the data structure
        char bufferRead[56] = {0};
        int value = read(socketServer, bufferRead, 56);
        //transfer the data in buffer to the data structure-fill/////////////////////

    }

    //closing the socket
    close(socketServer);
}


/**
 * Class for OpenServerCommand
 */
 //constructor
OpenServerCommand::OpenServerCommand(){};
int OpenServerCommand::execute(vector<string> arrayStr, int i) {
    cout<<"in open server"<<endl;
    port = stoi(arrayStr[i+1]);
    //open thread to to connect
    thread threadServer(openDataServer,port);
    threadServer.join();
    return 2;
};
//destructor
OpenServerCommand::~OpenServerCommand(){};

/**
 * Class for ConnectCommand
 */
ConnectCommand::ConnectCommand(){};

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
    }
    else{
        std::cerr << "connected to server" << std::endl;
    }
}

int ConnectCommand::execute(vector<string> arrayStr, int i) {
    cout<<"in connect command"<<endl;

    adress = arrayStr[i+1];
    port= stoi(arrayStr[i+2]);
    std::thread threadClient(connectControlClient,adress, port);
    threadClient.join();
    return 4;
}
//destructor
ConnectCommand::~ConnectCommand(){};


/**
 * Class for DefineVarCommand
 */
 //constructor
DefineVarCommand::DefineVarCommand(int num)
    : index(num){};

int DefineVarCommand::execute(vector<string> arrayStr, int i) {
    cout<<"in var def"<<endl;
    /**need to change this func**///////////////////////////////////////////////////////////////////////
    index=i;
    if (arrayStr[index+1].compare("=")==0){
        return 2;
    }else if ((arrayStr[index+1].compare("while"))||(arrayStr[index+1].compare("for"))||
              (arrayStr[index+1].compare("if"))){
        return 1;
    }else if ((arrayStr[index+2].compare("sim")==0)) {
        return 5;
    }else{
        return 0;
    }
}
//destructor
DefineVarCommand::~DefineVarCommand(){};



/**
 * Class for ConditionParser
 */
//constructor
ConditionParser::ConditionParser(){};
//destructor
ConditionParser::~ConditionParser(){};


/**
 * Class for ifCommand
 */
//constructor
ifCommand::ifCommand(int num)
    : index(num){};
int ifCommand::execute(vector<string> arrayStr, int i) {
    cout<<"in if command "<<endl;
    return 0 ;                              //????????????????????
}
//destructor
ifCommand::~ifCommand(){};


/**
 * Class for loopCommand
 */
//constructor
loopCommand::loopCommand(int num): index(num){};
int loopCommand::execute(vector<string> arrayStr, int i) {
    /**need to change this func**///////////////////////////////////////////////////////////////////////
    while (arrayStr[index] != "}"){
        cout<<"in while  "<<arrayStr[index]<<endl;
        index++;
        num++;
    }
    return num;
}
//destructor
loopCommand::~loopCommand(){};


/**
 * Class for Print
 */
//constructor
Print::Print(){};
int Print::execute(vector<string> arrayStr, int i) {
    //print the string
    cout<<arrayStr[i+1]<<"_-----" << endl;
    return 2;
}
//destructor
Print:: ~Print(){};

/**
 * Class for Sleep
 */
//constructor
Sleep::Sleep(){};
int Sleep::execute(vector<string> arrayStr, int i) {
    // sleep(stoi(arrayStr[i+1]));                           //??????????????????????????????
    cout<<"sleep  "<<stoi(arrayStr[i+1])<<endl;
    return 2;
}
//destructor
Sleep::~Sleep(){};


