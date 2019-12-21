//
// Created by noa on 06/11/2019.
//


#include "Expression.h"
#include <iostream>
#include <string>
#include <map>

#ifndef EX1_EX1_H
#define EX1_EX1_H

class Value : public Expression {
  const double value;
 public:
  Value(double v);
  double calculate();
};
class var : public Expression {
  string name;
  double value;
 public:
  var(string nameOfVer, double valueOfVer);
  double calculate();
  //~Variable();

  var &operator++();

  var &operator--();

  var &operator+=(double number);

  var &operator-=(double number);

  var &operator++(int number);

  var &operator--(int number);
};

class BinaryOperation :public Expression{
 protected:
  Expression *rightExp;
  Expression *leftExp;
 public:
  BinaryOperation(Expression *exp1, Expression *exp2);
  ~BinaryOperation();
};

class UnaryExpression :public Expression{
 protected:
  Expression *exp;
 public:
  UnaryExpression(Expression *exp1);
  ~UnaryExpression();
};

class Minus : public BinaryOperation {
 public:
  Minus(Expression *exp11, Expression *exp21);
  double calculate();
};

class Plus : public BinaryOperation {
 public:
  Plus(Expression *exp11, Expression *exp21);
  double calculate();
};

class Mul : public BinaryOperation {
 public:
  Mul(Expression *exp11, Expression *exp21);
  double calculate();
};

class Div : public BinaryOperation {
 public:
  Div(Expression *exp11, Expression *exp21);
  double calculate();
};

class UPlus : public UnaryExpression {
 public:
  UPlus(Expression *exp1);
  //calculate
  double calculate();
};

class UMinus : public UnaryExpression {
 public:
  UMinus(Expression *exp11);
  //calculate
  double calculate();
};

class Inter {
 public:
  char *saveStr;
  map<string, double > mapVar;
  Expression *toInsert;
  Expression *one;
  Expression *two;
  Expression *newExp;
  Inter();
  Expression *interpret(string toExp);
  void setVariables(string set);
};


#endif //EX1_EX1_H
