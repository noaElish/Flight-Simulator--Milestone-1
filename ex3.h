#ifndef EX3__COMMAND_H_
#define EX3__COMMAND_H_
#include <iostream>
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <unistd.h>
#include <unordered_set>

using namespace std;
/**
 * command Interface
 */
class Command {
public:
    virtual int execute(vector<string> arrayStr, int i) = 0;
    //destructor
    ~Command(){};
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

/**
 * Class for OpenServerCommand
 */
class OpenServerCommand : virtual public Command{
protected:
    int port;
public:
    //constructor
    OpenServerCommand(){};
    int execute(vector<string> arrayStr, int i) {
        port = stoi(arrayStr[i+1]);
        //open thread to to connect
       // thread threadServer(openDataServer,port);
        cout<<"in open server"<<endl;
        return 2;
    };
    //destructor
    ~OpenServerCommand(){};
};

/**
 * Class for ConnectCommand
 */
class ConnectCommand : public Command{
public:
    ConnectCommand(){};
    int execute(vector<string> arrayStr, int i) {

        cout<<"in connect command"<<endl;
        return 4;
    }
    //destructor
    ~ConnectCommand(){};
};

/**
 * Class for DefineVarCommand
 */
class DefineVarCommand : public Command{
private:
    int index;
public:
    DefineVarCommand(int num): index(num){};
    DefineVarCommand(){};  //every class will have a default constructor
    int execute(vector<string> arrayStr, int i) {
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
    ~DefineVarCommand(){};
};

/**
 * Class for ConditionParser
 */
class ConditionParser : public Command{
public:
    //constructor
    ConditionParser(){};
    //destructor
    ~ConditionParser(){};
};

/**
 * Class for ifCommand
 */
class ifCommand : public ConditionParser{
private:
    int index;
public:
    //constructor
    ifCommand(int num): index(num){};
    int execute(vector<string> arrayStr, int i) {
        cout<<"in if command "<<endl;
        return 0 ;                              //????????????????????
    }
    //destructor
    ~ifCommand(){};
};

/**
 * Class for loopCommand
 */
class loopCommand : public ConditionParser{
private:
    int index;
    int num=0;
public:
    loopCommand(int num): index(num){};
    loopCommand(){};//every class will have a default constructor
    int execute(vector<string> arrayStr, int i) {
       /**need to change this func**///////////////////////////////////////////////////////////////////////
        while (arrayStr[index] != "}"){
            cout<<"in while  "<<arrayStr[index]<<endl;
            index++;
            num++;
        }
        return num;
    }
    //destructor
    ~loopCommand(){};
};

/**
 * Class for Print
 */
class Print : public Command{
public:
    //constructor
    Print(){};
    virtual int execute(vector<string> arrayStr, int i) {
        //print the string
        cout<<arrayStr[i+1]<<"_-----" << endl;
        return 2;
    }
    //destructor
    ~Print(){};
};


/**
 * Class for Sleep
 */
class Sleep : public Command{
public:
    //constructor
    Sleep(){};
    virtual int execute(vector<string> arrayStr, int i) {
       // sleep(stoi(arrayStr[i+1]));                           //??????????????????????????????
        cout<<"sleep  "<<stoi(arrayStr[i+1])<<endl;
        return 2;
    }
    //destructor
    ~Sleep(){};
};











/**
 * Class for Ex3
 * This class contains auxiliary functions for Main
 */
class Ex3 {
public:


    //This function deletes unnecessary spaces from words
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

    //This function divides the text into separate words and put them in array
    vector<string> splitLine(string line, vector<string> splittedStrings ){
        int i=0;
        int j=0;
        string token;
        string word;
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
            } else if (line[i]==' '){
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

    //This function reads a text from a file and inserts it into an array
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

    //This function builds a map of strings and commands
    map <string, Command*> intoCommandMap(vector<string> splittedStrings,map <string, Command*> commandMap ){
        string key;
        Command* val = nullptr;
        int num=0;
        //iterator for vector
        vector<string>::const_iterator iter;
        for (iter = splittedStrings.begin(); iter != splittedStrings.end(); ++iter){
            key = splittedStrings[num];
            if (key.compare("openDataServer")==0){
                val = new OpenServerCommand();
                commandMap.insert({key, val});
            } else if (key.compare("connectControlClient")==0){
                val = new ConnectCommand();
                commandMap.insert({key, val});
            } else if (key.compare("Print")==0){
                val = new Print();
                commandMap.insert({key, val});
            }else if (key.compare("Sleep")==0){
                val = new Sleep();
                commandMap.insert({key, val});
            }else if (key.compare("var") ==0){              /**need to change this**/

                key = splittedStrings[num+1];
                val = new DefineVarCommand(num+1);
                commandMap.insert({key, val});
            }else if ((key.compare("while") ==0)||(key.compare("for") ==0)||(key.compare("if") ==0)){

                if ((key.compare("while") ==0)||(key.compare("for") ==0)){
                    key = splittedStrings[num+1];
                    val = new loopCommand(num);
                    commandMap.insert({key, val});
                }else{ // key= "if"
                    key = splittedStrings[num+1];
                    val = new ifCommand(num);
                    commandMap.insert({key, val});
                }
            }
            num++;
        }
        /*
        print the map
        for(auto it = commandMap.begin(); it != commandMap.end(); ++it)
        {
            cout << "key:  " << it->first<<endl;
            cout << "value:  " << it->second<<endl;
        }
         */
        return commandMap;
    }

    //This function goes on array and executes the commands
    void parser (vector<string> splittedStrings){
        //map to commands
        map <string, Command*> commandMap;
        commandMap = intoCommandMap(splittedStrings, commandMap);
        //execute all the commands
        int i;
        int indexJump=0;
        Command* c;
        for (i=0; i<splittedStrings.size(); i++){
            if (commandMap.count(splittedStrings[i])!=0){
                c=commandMap.find(splittedStrings[i])->second;
                indexJump = c->execute(splittedStrings, i);
                i=i+indexJump-1;
            }
        }
    }
    //destructor
    ~Ex3(){};
};


#endif //EX3__COMMAND_H_

