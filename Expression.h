//
// Created by shira on 21.11.2019.
//

#ifndef UNTITLED1_EXPRESSION_H
#define UNTITLED1_EXPRESSION_H

#ifndef PROJECT_EXPRESSION_H
#define PROJECT_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //PROJECT_EXPRESSION_H
#endif //UNTITLED1_EXPRESSION_H
