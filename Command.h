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
#include <arpa/inet.h>
#include <map>

using namespace std;
//command Interface


class Command {

 public:
  virtual int execute(vector<string> arrayStr) = 0;
  ~Command();
};

std::map<string,Command*> intoCommandMap;

//function of open Command
void openDataServer(int port) {
  //creating new socket
  int socketServer = socket(AF_INET, SOCK_DGRAM, 0);
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
  if (bind(socketServer, (struct sockaddr *) &addressSer, sizeof(addressSer)) == -1) {
    std::cerr << "cant bind socket to ip" << std::endl;
  }

  //listen to the port
  if (listen(socketServer, 5) == -1) {
    std::cerr << "cant listen to ip" << std::endl;
  }

  //accept the client- flight gear
  if (accept(socketServer, (struct sockaddr *) &addressSer, (socklen_t *) &addressSer) == -1) {
    std::cerr << "cant accept client" << std::endl;
  }

  //reading from the socket line by line-use loop
  for (int i = 0; i < 23; i++) {
    //save each line to the data structure
    char bufferRead[1024] = {0};
    int value = read(socketServer, bufferRead, 1024);
    //transfer the data in buffer to the data structure-fill/////////////////////

  }

  //closing the socket
  close(socketServer);
}
class OpenServerCommand : public Command {
 public:
  virtual int execute(vector<string> arrayStr) {
    //open thread to to connect
    ////////change- need to get the port to this function instead of 5400///////
    std::thread threadServer(openDataServer, 5400);
   return 2;
  }
};


//function of connect Command
void connectControlClient(string adress, int port) {

  //create new socket
  int socketClient = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketClient == -1) {
    std::cerr << "cant create socket" << std::endl;
  }

  //create the object for the bind
  sockaddr_in addressSer;
  addressSer.sin_family = AF_INET;
  //change to adress
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
class ConnectCommand : public Command {

 public:
  virtual int execute(vector<string> arrayStr) {
    //open thread- as the client
    ///////////////////change to parameters////////////////
    std::thread threadClient(connectControlClient, "127.0.0.1", 5402);
    return 2;
  }
};

class DefineVarCommand : public Command {
 public:
  virtual int execute() {
  }
};

#endif //EX3__COMMAND_H_

