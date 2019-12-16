//
// Created by noa on 16/12/2019.
//

#ifndef EX3__COMMAND_H_
#define EX3__COMMAND_H_
#include <iostream>

#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <unistd.h>

using namespace std;
/**
 * command Interface
 */


class Command {

 public:
  virtual int execute() = 0;
  ~Command();
};

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

  //reading from the socket line by line-use loop
  //////////////////////fill//////////////////////

  //closing the socket
  close(socketServer);
}


class OpenServerCommand : public Command{
 public:
  virtual int execute(vector<string> arrayStr){
    //open thread to to connect
    ////////change- need to get the port to this function instead of 5400///////
    std::thread threadServer(openDataServer,5400);
  }
  //~OpenServerCommand;
};

class ConnectCommand : public Command{

 public:
  virtual int execute(){

  }
  //destructor
  //~ConnectCommand;
};

class DefineVarCommand : public Command{

 public:
  virtual int execute(){

  }
  //destructor
  //~DefineVarCommand;
};

#endif //EX3__COMMAND_H_
