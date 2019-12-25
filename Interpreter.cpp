#include <mutex>
#include "Interpreter.h"
#include "Expression.h"
#include "ex1.h"

int data_received=0;
bool done = true;
std:: mutex mutaxMaps;
//constructor
Interpreter::Interpreter() {};

//This function deletes unnecessary spaces from words
string Interpreter::trim(const string &str) {
    size_t first = str.find_first_not_of("\t\n\v\f\r ");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of("\t\n\v\f\r ");
    return str.substr(first, (last - first + 1));
}

//This function divides the text into separate words and put them in array
vector<string> Interpreter::splitLine(string line, vector<string> splittedStrings) {
    int i = 0;
    int j = 0;
    string token;
    string word;
    while (i < line.length()) {
        if (line[i] == '"') {
            j = i + 1;
            while (j < line.length()) {
                if (line[j] == '\"') {
                    token = line.substr(0, j + 1);
                    splittedStrings.push_back(trim(token));
                    line = trim(line.erase(0, j + 1));
                }
                j++;
            }
            if (!(line[0] == ',')) {
                break;
            }
        } else if (line[i] == ' ') {
            token = line.substr(0, line.find(' '));
            splittedStrings.push_back(trim(token));

            line = trim(line.erase(0, line.find(' ') + 1));
            i = 0;
        } else if (line[i] == '(') {
            token = line.substr(0, line.find('('));
            splittedStrings.push_back(trim(token));
            line = trim(line.erase(0, line.find('(') + 1));
            i = 0;
        } else if (line[i] == ')') {
            token = line.substr(0, line.find(')'));
            splittedStrings.push_back(trim(token));
            line = trim(line.erase(0, line.find(')') + 1));
            i = 0;
        } else if (line[i] == ',') {
            if (!(line[0] == ',')) {
                token = line.substr(0, line.find(','));
                splittedStrings.push_back(trim(token));
            }
            line = trim(line.erase(0, line.find(',') + 1));
            i = 0;
        } else if (((line[i] == '<') || (line[i] == '>')) && (line[i + 1] == '=')) {
            if (line[i] == '<') {
                splittedStrings.push_back("<=");
                line = trim(line.erase(0, line.find('<') + 2));
            } else {
                splittedStrings.push_back(">=");
                line = trim(line.erase(0, line.find('>') + 2));
            }
            i = 0;
        } else if (line[i] == '=') {
            splittedStrings.push_back("=");
            token = line.substr(line.find('=') + 1);
            splittedStrings.push_back(trim(token));
            break;
        } else if (line[i] == '{') {
            splittedStrings.push_back("{");
            break;
        } else if (line[i] == '}') {
            splittedStrings.push_back("}");
            break;
        } else {
            i++;
        }
    }
    return splittedStrings;
}

//This function reads a text from a file and inserts it into an array
vector<string> Interpreter::lexer(char *fileName) {
    fstream file(fileName, ios::in);
    if (!file) {
        //couldn't open the file.
        throw "error with file";
    } else {
        //vector for all words in file
        vector<string> splittedStrings;
        string line{};
        while (!file.eof()) {
            getline(file, line);
            //split the line to words
            splittedStrings = splitLine(line, splittedStrings);
        }
        return splittedStrings;
    }
}

//This function builds a map of strings and commands
map<string, Command *> Interpreter::intoCommandMap(vector<string> splittedStrings, map<string, Command *> commandMap) {
    string key;
    string direction;
    float value;
    Command *val = nullptr;
    int num = 0;
    //iterator for vector
    vector<string>::const_iterator iter;
    for (iter = splittedStrings.begin(); iter != splittedStrings.end(); ++iter) {
        key = splittedStrings[num];
        if (key.compare("openDataServer") == 0) {
            val = new OpenServerCommand();
            commandMap.insert({key, val});
        } else if (key.compare("connectControlClient") == 0) {
            val = new ConnectCommand();
            commandMap.insert({key, val});
        } else if (key.compare("Print") == 0) {
            val = new Print();
            commandMap.insert({key, val});
        } else if (key.compare("Sleep") == 0) {
            val = new Sleep();
            commandMap.insert({key, val});
        } else if (key.compare("var") == 0) {              /**need to change this**/
            /*
                key = splittedStrings[num + 1];
                val = new DefineVarCommand();
                commandMap.insert({key, val});
                Variable *var = new Variable(0, splittedStrings[num + 4], splittedStrings[num + 2]);
                SymbolTable *symbolsMaps = symbolsMaps->getInstance();
                symbolsMaps->upDateSymbolTable(splittedStrings[num + 1], *var);
                */

            //check if there is "->\<-" or "="
            if (splittedStrings[num+2]== "="){
                //take the value of the second variable
                Inter *i1 = new Inter();
                Expression *next;                                                                      //////////////////////////////////////////

                next = i1->interpret(splittedStrings[num + 3]);
                cout<<"**"<<splittedStrings[num + 3]<<endl;
//                cout<<"split3:   "<<splittedStrings[num+3]<<endl;
                float save= next->calculate();
                cout<<"save: "<<save<<endl;

                //create new var
                val = new DefineVarCommand();
                commandMap.insert({key, val});
                Variable *var = new Variable(save, "=", splittedStrings[num + 2],0);
                //Variable *var = new Variable(save, "", splittedStrings[num + 2]);
                SymbolTable *symbolsMaps = symbolsMaps->getInstance();
                symbolsMaps->upDateSymbolTable(splittedStrings[num + 1], *var);

            } else{
                key = splittedStrings[num + 1];
                val = new DefineVarCommand();
                commandMap.insert({key, val});
                Variable *var = new Variable(0, splittedStrings[num + 4], splittedStrings[num + 2],0);
                SymbolTable *symbolsMaps = symbolsMaps->getInstance();
                symbolsMaps->upDateSymbolTable(splittedStrings[num + 1], *var);
            }



            /*
            cout<<"var:  "<<var->getVar()<<endl;
            cout<<"dir:  "<<var->getDir()<<endl;
            cout<<"sim   "<<var->getSim()<<endl;
            */
        } else if ((key.compare("while") == 0) || (key.compare("for") == 0) || (key.compare("if") == 0)) {

            if ((key.compare("while") == 0) || (key.compare("for") == 0)) {
                cout<<"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"<<endl;
                key = splittedStrings[num];
                val = new loopCommand(num);
                commandMap.insert({key, val});
            } else { // key= "if"
                key = splittedStrings[num + 1];
//                val = new ifCommand(num);
                commandMap.insert({key, val});
            }
        }
        num++;
    }
    return commandMap;
}


std::mutex mutexParser;
//This function goes on array and executes the commands
void Interpreter::parser(vector<string> splittedStrings) {
    //map to commands
    map<string, Command *> commandMap;
    commandMap = intoCommandMap(splittedStrings, commandMap);
    //instance to symbol table
    SymbolTable *symbolsMaps = symbolsMaps->getInstance();
    //symbolsMaps->intilizationCommandMap(splittedStrings);
    //execute all the commands
    int i;
    int indexJump = 0;
    Command *c;
   // mutexParser.lock();
    for (i = 0; i < splittedStrings.size(); i++) {
        if (commandMap.count(splittedStrings[i]) != 0) {
           // cout<<"sss: "<<splittedStrings[i]<<"   "<<splittedStrings[i+1]<<endl;
            if ((i!=0)&&(splittedStrings[i-1]!="var")&&(splittedStrings[i]!="var")&&(splittedStrings[i-1]!="=")){
                cout<<"start execute    +"<<splittedStrings[i]<<endl;
                c = commandMap.find(splittedStrings[i])->second;

               // data_received=1;
//mutuxParser.lock();
                indexJump = c->execute(splittedStrings, i);
//mutuxParser.unlock();
                cout<<"end execute"<<endl;
                i = i + indexJump - 1;
            }
            if (i==0){
                cout<<"33333"<<endl;
                c = commandMap.find(splittedStrings[i])->second;
                indexJump = c->execute(splittedStrings, i);
                i = i + indexJump - 1;
            }
        }
        if ((splittedStrings[i-1]=="var")&&(splittedStrings[i+1]=="=")){



            cout<<"4444444"<<endl;

            commandMap.insert({splittedStrings[i],  new DefineVarCommand()});
            Variable *var = new Variable(0, "=", splittedStrings[i + 2],0);
            SymbolTable *symbolsMaps = symbolsMaps->getInstance();
            symbolsMaps->upDateSymbolTable(splittedStrings[i], *var);

            //data_received=1;

            c = commandMap.find(splittedStrings[i])->second;
            indexJump = c->execute(splittedStrings, i);
            i = i + indexJump - 1;
        }
    }
   // mutexParser.unlock();
  data_received=1;
}

//destructor
Interpreter::~Interpreter() {};

/**
 * Class Variable
 */
//constructor
Variable::Variable(float value, string simString, string directionString, int updateS)
        : value(value), update(updateS){
    sim = simString;
    direction = directionString;
   // update= updateS;
};
//this method update the value
void Variable::updateValue(float num) {
    value = num;
}
void Variable::updateStat(int num) {
    update = num;
}
//return the direction of a certain variable
string Variable::getDir() {
    return this->direction;
}
//return the sim path of a certain variable
string Variable::getSim() {
    return this->sim;
}
//return the numeric value of a certain variable
float Variable::getVar() {
    return this->value;
}
int Variable::getUpdate(){
    return this->update;
}
//constructor
Variable::~Variable() {};

/**
 * Class SymbolTable
 */
//This method allows you to get the pointer to the only object created.
/* Null, because instance will be initialized on demand. */
SymbolTable *SymbolTable::instance = 0;

//return instance for the map
SymbolTable *SymbolTable::getInstance() {
    if (instance == 0) {
        instance = new SymbolTable();
    }
    return instance;
}

//constructor - It is in the private area so objects cannot be created from outside.
SymbolTable::SymbolTable() {};
SymbolTable *symbolsMaps = symbolsMaps->getInstance();
SymbolTable *simMap = symbolsMaps->getInstance();

//insert value to the command map
void SymbolTable::intilizationCommandMap(vector<string> splittedStrings) {
    mutaxMaps.lock();
    map<string, Command *> commandMap;
    Interpreter i;
    commandMap = i.intoCommandMap(splittedStrings, commandMap);
    mutaxMaps.unlock();
}

//update a certain value in the symbol map
void SymbolTable::upDateSymbolTable(string nameVar, Variable var) {
    mutaxMaps.lock();
    instance->symbolTable.insert({nameVar, var});
    mutaxMaps.unlock();
}

//return the variable of a certain key in the symbol map
Variable SymbolTable::getVariable(string name) {
    mutaxMaps.lock();
    symbolsMaps->symbolTable.find(name);
    mutaxMaps.unlock();
}

//insert new value to sim map
void SymbolTable::putInSimMap(int i, float num) {
    mutaxMaps.lock();
    SymbolTable *instance = SymbolTable::getInstance();
    string simString = symbolsMaps->SetArrayOfSim(i);
    instance->simMap.insert({simString, num});
    mutaxMaps.unlock();
}

//get the value of a certain sim in the sim map
float SymbolTable::getValueFromSim(string sim) {
    mutaxMaps.lock();
    float returnIt;
    auto search = simMap.find(sim);
    if (search != simMap.end()) {
        returnIt = search->second;
    }
    mutaxMaps.unlock();
    return returnIt;
}

//create array of sim paths
string SymbolTable::SetArrayOfSim(int i) {
    mutaxMaps.lock();
    string arrSim[36];
    arrSim[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    arrSim[1] = "/sim/time/warp";
    arrSim[2] = "/controls/switches/magnetos";
    arrSim[3] = "//instrumentation/heading-indicator/offset-deg";
    arrSim[4] = "/instrumentation/altimeter/indicated-altitude-ft";
    arrSim[5] = "/instrumentation/altimeter/pressure-alt-ft";
    arrSim[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    arrSim[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    arrSim[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    arrSim[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
    arrSim[10] = "/instrumentation/encoder/indicated-altitude-ft";
    arrSim[11] = "/instrumentation/encoder/pressure-alt-ft";
    arrSim[12] = "/instrumentation/gps/indicated-altitude-ft";
    arrSim[13] = "/instrumentation/gps/indicated-ground-speed-kt";
    arrSim[14] = "/instrumentation/gps/indicated-vertical-speed";
    arrSim[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
    arrSim[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    arrSim[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    arrSim[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
    arrSim[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    arrSim[20] = "/controls/flight/aileron";
    arrSim[21] = "/controls/flight/elevator";
    arrSim[22] = "/controls/flight/rudder";
    arrSim[23] = "/controls/flight/flaps";
    arrSim[24] = "/controls/engines/engine/throttle";
    arrSim[25] = "/controls/engines/current-engine/throttle";
    arrSim[26] = "/controls/switches/master-avionics";
    arrSim[27] = "/controls/switches/starter";
    arrSim[28] = "/engines/active-engine/auto-start";
    arrSim[29] = "/controls/flight/speedbrake";
    arrSim[30] = "/sim/model/c172p/brake-parking";
    arrSim[31] = "/controls/engines/engine/primer";
    arrSim[32] = "/controls/engines/current-engine/mixture";
    arrSim[33] = "/controls/switches/master-bat";
    arrSim[34] = "/controls/switches/master-alt";
    arrSim[35] = "/engines/engine/rpm";
    mutaxMaps.unlock();
    return arrSim[i];
}

//destructor
SymbolTable::~SymbolTable() {};