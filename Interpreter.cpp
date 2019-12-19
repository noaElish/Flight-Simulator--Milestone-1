//
// Created by shira on 19.12.2019.
//

#include "Interpreter.h"

//constructor
Interpreter::Interpreter(){};


//This function deletes unnecessary spaces from words
string Interpreter::trim(const string& str)
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
vector<string> Interpreter::splitLine(string line, vector<string> splittedStrings ){
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
vector<string> Interpreter::lexer(char* fileName){
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
map <string, Command*> Interpreter::intoCommandMap(vector<string> splittedStrings,map <string, Command*> commandMap ){
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

            Variable *var = new Variable(0, splittedStrings[num+4]);    /**************/
            SymbolTable *symbolsMaps = symbolsMaps->getInstance();
            symbolsMaps->upDateSymbolTable(key, *var);


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
void Interpreter::parser (vector<string> splittedStrings){
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
Interpreter::~Interpreter(){};







/*
Variable *Variable::getInstance(){
    int value = 1;
    string sim = " ";
    static Variable varInstance(value, sim);
    return &varInstance;
}
 */
/**
 * Class Variable
 */

//constructor
Variable:: Variable(int value, string sim){};
//constructor
Variable::~Variable(){};



/**
 * Class SymbolTable
 */


//This method allows you to get the pointer to the only object created.
/* Null, because instance will be initialized on demand. */
SymbolTable* SymbolTable::instance = 0;

SymbolTable* SymbolTable::getInstance(){
    if (instance == 0)
    {
        instance = new SymbolTable();
    }

    return instance;
}
//constructor - It is in the private area so objects cannot be created from outside.
SymbolTable::SymbolTable(){};


SymbolTable *symbolsMaps = symbolsMaps->getInstance();
SymbolTable *simMap = symbolsMaps->getInstance();

void SymbolTable::upDateSymbolTable(string nameVar,Variable var){
    instance->symbolTable.insert({nameVar,var});
}

Variable getVariable(string name){
    symbolsMaps->symbolTable.find(name);
}


void SymbolTable::putInSimMap (int i, float num){
    SymbolTable* instance = SymbolTable::getInstance();
    string *arrSim = symbolsMaps->SetArrayOfSim();
    instance->simMap.insert({arrSim[int(i)],num});
    cout<<"string: "<<arrSim[int(i)]<<endl;
    cout<<"float: "<<num<<endl;

}



string* SymbolTable::SetArrayOfSim(){
    string arrSim[36];
    arrSim[0]= "/instrumentation/airspeed-indicator/indicated-speed-kt";
    arrSim[1]="/sim/time/warp";
    arrSim[2]="/controls/switches/magnetos";
    arrSim[3]="//instrumentation/heading-indicator/offset-deg";
    arrSim[4]="/instrumentation/altimeter/indicated-altitude-ft";
    arrSim[5]="/instrumentation/altimeter/pressure-alt-ft";
    arrSim[6]="/instrumentation/attitude-indicator/indicated-pitch-deg";
    arrSim[7]="/instrumentation/attitude-indicator/indicated-roll-deg";
    arrSim[8]="/instrumentation/attitude-indicator/internal-pitch-deg";
    arrSim[9]="/instrumentation/attitude-indicator/internal-roll-deg";
    arrSim[10]="/instrumentation/encoder/indicated-altitude-ft";
    arrSim[11]="/instrumentation/encoder/pressure-alt-ft";
    arrSim[12]="/instrumentation/gps/indicated-altitude-ft";
    arrSim[13]="/instrumentation/gps/indicated-ground-speed-kt";
    arrSim[14]="/instrumentation/gps/indicated-vertical-speed";
    arrSim[15]="/instrumentation/heading-indicator/indicated-heading-deg";
    arrSim[16]="/instrumentation/magnetic-compass/indicated-heading-deg";
    arrSim[17]="/instrumentation/slip-skid-ball/indicated-slip-skid";
    arrSim[18]="/instrumentation/turn-indicator/indicated-turn-rate";
    arrSim[19]="/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    arrSim[20]="/controls/flight/aileron";
    arrSim[21]="/controls/flight/elevator";
    arrSim[22]="/controls/flight/rudder";
    arrSim[23]="/controls/flight/flaps";
    arrSim[24]="/controls/engines/engine/throttle";
    arrSim[25]="/controls/engines/current-engine/throttle";
    arrSim[26]="/controls/switches/master-avionics";
    arrSim[27]="/controls/switches/starter";
    arrSim[28]="/engines/active-engine/auto-start";
    arrSim[29]="/controls/flight/speedbrake";
    arrSim[30]="/sim/model/c172p/brake-parking";
    arrSim[31]="/controls/engines/engine/primer";
    arrSim[32]="/controls/engines/current-engine/mixture";
    arrSim[33]="/controls/switches/master-bat";
    arrSim[34]="/controls/switches/master-alt";
    arrSim[35]="/engines/engine/rpm";


/*
 int t=0;
    cout<<arrSim->size()<<endl;
    while (t<36){
        cout<<arrSim[t]<<endl;
        t++;
    }
    cout<<t;
    */

}
//destructor
SymbolTable:: ~SymbolTable(){};



//SymbolTable *symbolTable = SymbolTable::getInstance();