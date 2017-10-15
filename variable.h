#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "term.h"

class Struct;

using std::string;
using std::vector;

class Variable : public Term {
public:
    Variable(string s, string typeName = "Variable") : Term(typeName), _symbol(s) {}
    string symbol() { return _symbol; }
    string value();
    
    void setValue(string value) {
        _value = value;
    }
    
    Struct *matchStruct() {
        return _matchStruct;
    }
    
    void setMatchStruct(Struct *structure) {
        _matchStruct = structure;
    }
    
    bool isUpdateValueForMatchVariablesSuccess(string value, Term *term);
    bool isUpdateValueForMatchVariablesSuccess(string value);
    
//    bool isUpdateValueForMatchVariablesSuccess(string value, SimpleObject *simpleObject) {
//        Variable *variable = dynamic_cast<Variable *>(simpleObject);
//        for (Variable *var : _matchVariables) {
//            if (!var->isAssignable(simpleObject) && !variable) {
//                return false;
//            }
//            var->setValue(value);
//        }
//        if (_matchStruct) {
//            _matchStruct->variable()->setValue(value);
//        }
//        setValue(value);
//        return true;
//    }
    
    vector<Variable *> *matchVariables() { return &_matchVariables; }
    
    string printMatchVariables() {
        string toString = "";
        for (Variable *variable : _matchVariables) {
            toString +=  "symbol = " + variable->symbol() + " value = " + variable->value();
        }
        return toString;
    }
    
    bool isAssignable(Term *term, string value) {
        //        Variable *variable = dynamic_cast<Variable *>(term);
        //        if (variable) {
        //            return true;
        //        }
        for (Variable *var : _matchVariables) {
            if (_value == var->symbol()) {
                return true;
            }
        }
        return _value == "" || _value == term->symbol() || _value == value;
    }
    
    bool isAssignable(Term *term) {
//        Variable *variable = dynamic_cast<Variable *>(term);
//        if (variable) {
//            return true;
//        }
        for (Variable *var : _matchVariables) {
            if (_value == var->symbol()) {
                return true;
            }
        }
        return _value == "" || _value == term->symbol();
    }
    
    void addMatchVariable(Variable *variable) {
        if (!isExistInVectors(variable) && symbol() != variable->symbol()) {
            _matchVariables.push_back(variable);
        }
        for (Variable *var : *(variable->matchVariables())) {
            if (!isExistInVectors(var) && symbol() != var->symbol()) {
                _matchVariables.push_back(variable);
            }
        }
        for (Variable *var : _matchVariables) {
            for (Variable *variable : _matchVariables) {
                if (!var->isExistInVectors(variable) && var->symbol() != variable->symbol()) {
                    var->matchVariables()->push_back(variable);
                }
            }
        }
    }
    
    bool isExistInVectors(Variable *variable) {
        bool isExist = false;
        for (Variable *var : _matchVariables) {
            if (var->symbol() == variable->symbol()) {
                isExist = true;
            }
        }
        return isExist;
    }
private:
    string const _symbol;
    string _value;
    Struct *_matchStruct = nullptr;
    vector<Variable *> _matchVariables;
};

#endif
