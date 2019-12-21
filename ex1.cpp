//
// Created by noa elishmereni on 06/11/2019.
//

#include "ex1.h"
#include "Expression.h"
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include "regex"
using namespace std;

/*this function define class value
 * */
//constructor
Value::Value(double v) : value(v) {
}
//return the integer of value
double Value::calculate() {
  return (value);
}

/*this function define class variable
 * */
//constructor
var::var(string nameOfVer, double valueOfVer) {
  /*this->name = new char[strlen(nameOfVer) + 1];
  strcpy(this->name, nameOfVer);*/
  this->name = nameOfVer;
  this->value = valueOfVer;
}
//return the integer of value
double var::calculate() {
  double copy= value;
  return copy;
}

//return the ++value
var &var::operator++() {
  ++this->value;
  return *this;
}
//return the --value
var &var::operator--() {
  --this->value;
  return *this;
}
//return the value+double
var &var::operator+=(double number) {
  this->value = this->value + number;
  return *this;
}
//return the value-double
var &var::operator-=(double number) {
  this->value = this->value - number;
  return *this;
}
//return the value++
var &var::operator++(int) {
  this->value++;
  return *this;
}
//return the value--
var &var::operator--(int) {
  this->value--;
  return *this;
}


//constroctor
BinaryOperation::BinaryOperation(Expression *exp1, Expression *exp2) {
  this->leftExp = exp1;
  this->rightExp = exp2;
}
//destroctor
BinaryOperation::~BinaryOperation() {
  delete (rightExp);
  delete (leftExp);
}

UnaryExpression::UnaryExpression(Expression *exp1) {
  this->exp = exp1;
}
UnaryExpression::~UnaryExpression() {
  delete (exp);
}


//constructor*/
Minus::Minus(Expression *exp11, Expression *exp21) : BinaryOperation(exp11, exp21) {
}
//calculate
double Minus::calculate() {
  return (leftExp->calculate() - rightExp->calculate());
}

//constructor
Plus::Plus(Expression *exp11, Expression *exp21) : BinaryOperation(exp11, exp21) {

}
//calculate
double Plus::calculate() {
  return (leftExp->calculate() + rightExp->calculate());
}


//constructor
Mul::Mul(Expression *exp11, Expression *exp21) : BinaryOperation(exp11, exp21) {
}
//calculate
double Mul::calculate() {
  return (leftExp->calculate() * rightExp->calculate());
}

//constructor
Div::Div(Expression *exp11, Expression *exp21) : BinaryOperation(exp11, exp21) {
}
//calculate
double Div::calculate() {
  if (rightExp->calculate() == 0) {
    throw "error- division in zero";
  }
  return (leftExp->calculate() / rightExp->calculate());
}
//constructor*/
UPlus::UPlus(Expression *exp1) : UnaryExpression(exp1) {
}
//calculate
double UPlus::calculate() {
  return (exp->calculate());
}

//constructor
UMinus::UMinus(Expression *exp1) : UnaryExpression(exp1) {

}
//calculate
double UMinus::calculate() {
  return (-1 * exp->calculate());
}


//variables for the method
char *saveStr;
map<string, double> mapVar;
queue<string> expHolder;
stack<char> operHolder;
stack<Expression *> expressionStack;
Expression *toInsert;
Expression *one;
Expression *two;
Expression *newExp;

//the constructor of the class
Inter::Inter() {
}

//this method change a string to expression
//Expression *interpret(string toExp) {
Expression* Inter::interpret(string toExp) {

  //loop that goes over the string
  for (unsigned int i = 0; i < toExp.length(); i++) {

    //if there is space somewhere in the string
    if (toExp[i] == ' ') {
      continue;
    }

      //if the char is '('
    else if (toExp[i] == '(') {
      operHolder.push(toExp[i]);
    }

      //if the char is ")"
    else if (toExp[i] == ')') {
      string saveOperator;
      //move all the operator until you reach "("
      while (operHolder.top() != '(') {
        //save the top operator
        saveOperator = operHolder.top();
        //move the operator to the queue
        expHolder.push(saveOperator);
        operHolder.pop();
      }
    }

      //if the char is a number
    else if (isdigit(toExp[i])) {
      //loop to check how big the number is
      string saveNum;
      saveNum = toExp[i];
      //while it is still a digit, count by one
      while ((isdigit(toExp[i + 1]) || (toExp[i + 1] == '.'))) {
        saveNum = saveNum + toExp[i + 1];
        i++;
      }
      //push the number to the queue
      expHolder.push(saveNum);
    }

      //if the char is operator
    else {
      //if the operator is a variable
      if ((toExp[i] != '+') && (toExp[i] != '/') && (toExp[i] != '-') && (toExp[i] != '*')) {
        int countOne = 0;
        int copyI = i;
        std::string strinOperat;
        //checking if the variable name is longer then one char
        while ((toExp[copyI + 1] != '(') && (toExp[copyI + 1] != ')') && (toExp[copyI + 1] != '-')
            && (toExp[copyI + 1] != '+') && (toExp[copyI + 1] != '/') && (toExp[copyI + 1] != '*')) {
          countOne++;
          copyI++;
        }
        //if it is longer- save the given name
        if (countOne != 0) {
          strinOperat = toExp.substr(i, countOne + 1);
          i = i + countOne;
        }
          //if it is only one char
        else {
          strinOperat.push_back(toExp[i]);
        }
        //save the variable name
        expHolder.push(strinOperat);
        continue;
        //if it is an operator
      } else {
        //if its an operator, and its two operators one after another, throw exception
        if (toExp[i + 1] == toExp[i]) {
          throw "error";
        }
        //if the stack is empty
        if (operHolder.empty()) {
          //the stack is empty- and the first operator to enter is unary minus
          if (toExp[i] == '-') {
            if (i == 0) {
              //creating unique sign for the unary minus
              operHolder.push('$');
            } else {
              operHolder.push(toExp[i]);
            }
          } else {
            operHolder.push(toExp[i]);
          }
        }

          //if the stack isn't empty
        else {
          //compare the operator on the top
          char saveToCompare = operHolder.top();
          //if the operator is higher then the one on the top
          if (saveToCompare >= toExp[i]) {
            while (operHolder.top() != '(') {
              saveToCompare = operHolder.top();
              //move the operator to the queue
              std::string strinOperat = std::to_string(saveToCompare);
              expHolder.push(strinOperat);
              operHolder.pop();
            }
            //inserting the new operator
            if (toExp[i] == '-') {
              if (isdigit(toExp[i - 1])) {
                //creating unique sign for the unary minus
                operHolder.push('$');
              }
            } else {
              operHolder.push(toExp[i]);
            }
          }
            //if the operator is lower then the one on the top
          else {
            if (toExp[i] == '-') {
              if (((!isdigit(toExp[i - 1])) && (!isdigit(toExp[i + 1])))
                  || ((toExp[i + 1] != '(') && (toExp[i - 1] != ')'))) {
                //creating unique sign for the unary minus
                operHolder.push('$');
              } else {
                operHolder.push(toExp[i]);
              }
            } else {
              operHolder.push(toExp[i]);
            }
          }
        }
      }
    }
  }

  //after you finish going over the string, move all that's left in the stack to the queue
  while (!operHolder.empty()) {
    char save = operHolder.top();
    //if the operator is "(", dont pass and and continue
    if (save == '(') {
      operHolder.pop();
      continue;
      //if its a regular operator- pass it to queue
    } else {
      string moveToQueue;
      moveToQueue.push_back(save);
      expHolder.push(moveToQueue);
      operHolder.pop();
    }
  }

  //after the queue is ready- make a new expression from the string
  //search two numbers and an operator and make an expression from it
  double valueSave;
  string charSave;
  while (!expHolder.empty()) {
    //take out the numbers until you reach an operator
    while ((expHolder.front() != "+") && (expHolder.front() != "-") && (expHolder.front() != "/")
        && (expHolder.front() != "*") && (expHolder.front() != "$")) {
      //if this is a variable
      if (mapVar.count(expHolder.front())) {
        charSave = expHolder.front();
        //find the value in the map
        valueSave = mapVar[charSave];
        //create new expression of variable
        toInsert = new var(charSave, valueSave);
      } else {
        toInsert = new Value(std::stod(expHolder.front()));
      }
      expressionStack.push(toInsert);
      expHolder.pop();
    }

    //there is an operator in the string, take it and create new expression together with the last two values
    //save the last two values
    //if its $ sign- make only one expression
    if (expHolder.front() == "$") {
      one = expressionStack.top();
      expressionStack.pop();
      newExp = new UMinus(one);
      expressionStack.push(newExp);
      expHolder.pop();
    } else {
      if (expressionStack.size() >= 2) {
        one = expressionStack.top();
        expressionStack.pop();
        two = expressionStack.top();
        expressionStack.pop();
        //if there is only one expression on the top of the stack, but the operator isnt unary- exception
      } else {
        try {
          throw 1;
        }
        catch (int i) {
          std::cout << "error- not enough elements";
          break;
        }
      }
      //for each operator- save the matching expression
      if (expHolder.front() == "+") {
        newExp = new Plus(two, one);
        expressionStack.push(newExp);
      }
      if (expHolder.front() == "-") {
        newExp = new Minus(two, one);
        expressionStack.push(newExp);

      }
      if (expHolder.front() == "/") {
        newExp = new Div(two, one);
        expressionStack.push(newExp);
      }
      if (expHolder.front() == "*") {
        newExp = new Mul(two, one);
        expressionStack.push(newExp);

      }
      expHolder.pop();
    }
  }
  //return the full expression
  return expressionStack.top();
}

void Inter::setVariables(string stringA) {
  double doubSave;
  unsigned int j = 0;
  int p = 0;
  string charSave;
  regex regexCheck("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)))?");

  for (unsigned int i = 0; i < stringA.length(); i++) {
    if (stringA[i] == '=') {
      int count = 0;
      j = i;
      p = i;
      //count the number of chars to take from the string
      while ((stringA[p - 1] != ';') && (p > 0)) {
        p--;
        count++;
      }
      //save the name
      charSave = stringA.substr(p, count);

      count = 0;
      //count the number of chars to take from the string
      while ((j < stringA.length() - 1) && (stringA[j + 1] != ';')) {
        j++;
        count++;
      }
      //check if its a number
      if (regex_match(stringA.substr(i + 1, count), regexCheck)) {
        //if there are no problem with the expression, save to map
        doubSave = std::stod(stringA.substr(i + 1, count));
        if (mapVar.find(charSave) == mapVar.end()) {
          mapVar.insert(pair<string, double>(charSave, doubSave));
        } else {
          mapVar.erase(charSave);
          mapVar.insert(pair<string, double>(charSave, doubSave));
        }
      } else {
        throw "error regex";
      }
    }
  }
}

