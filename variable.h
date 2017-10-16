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
    string symbol() {
        return _symbol;
    }
    
    string value();
    
    void setValue(string value) {
        _value = value;
    }
    
    bool isUpdateValueForMatchVariablesSuccess(string value);
    
    Struct *matchStruct() {
        return _matchStruct;
    }
    
    void setMatchStruct(Struct *structure) {
        _matchStruct = structure;
    }
    
    vector<Variable *> *matchVariables() {
        return &_matchVariables;
    }
    
    string printMatchVariables() {
        string toString = "";
        for (Variable *variable : _matchVariables) {
            toString +=  "symbol = " + variable->symbol() + " value = " + variable->value();
        }
        return toString;
    }
    
    bool isAssignable(Term *term, string value) {
        for (Variable *var : _matchVariables) {
            if (_value == var->symbol()) {
                return true;
            }
        }
        return _value == "" || _value == term->symbol() || _value == value;
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
private:
    string const _symbol;
    string _value;
    Struct *_matchStruct = nullptr;
    vector<Variable *> _matchVariables;
    
    bool isExistInVectors(Variable *variable) {
        bool isExist = false;
        for (Variable *var : _matchVariables) {
            if (var->symbol() == variable->symbol()) {
                isExist = true;
            }
        }
        return isExist;
    }
};

#endif
