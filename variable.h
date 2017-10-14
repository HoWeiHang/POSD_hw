#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <vector>
#include "simpleObject.h"

using std::string;
using std::vector;

class Variable : public SimpleObject {
public:
    Variable(string s, string typeName = "Variable") : SimpleObject(typeName), _symbol(s) {}
    string symbol() const { return _symbol; }
	string value() { return _value; }
    
    void setValue(string value) {
        _value = value;
    }
    
    bool isUpdateValueForMatchVariablesSuccess (string value, SimpleObject *simpleObject) {
        Variable *variable = dynamic_cast<Variable *>(simpleObject);
        for (Variable *var : _matchVariables) {
            if (!var->isAssignable(simpleObject) && !variable) {
                return false;
            }
            var->setValue(value);
        }
        setValue(value);
        return true;
    }
//    void serMatchVariables(vector<Variable *> matchVariables) { _matchVariables = matchVariables; }
    vector<Variable *> *matchVariables() { return &_matchVariables; }
    
    string printMatchVariables() {
        string toString = "";
        for (Variable *variable : _matchVariables) {
            toString +=  "symbol = " + variable->symbol() + " value = " + variable->value();
        }
        return toString;
    }
    
    bool isAssignable(SimpleObject *simpleObject) {
        return _value == "" || _value == simpleObject->symbol();
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
    /*
    void addMatchVariable(Variable *variable) {
        if (!isExistInVectors(variable) && symbol() != variable->symbol()) {
            _matchVariables.push_back(variable);
        }
        for (Variable *var : _matchVariables) {
            if (!var->isExistInVectors(variable) && var->symbol() != variable->symbol()) {
                var->matchVariables()->push_back(variable);
            }
//            for (Variable *var : *(var->matchVariables())) {
//                if (!isExistInVectors(var) && _symbol != var->symbol()) {
//                    _matchVariables.push_back(var);
//                }
//            }
//            if (!variable->isExistInVectors(var) && var->symbol() != variable->symbol()) {
//                variable->matchVariables()->push_back(var);
//            }
        }
        for (Variable *var : *(variable->matchVariables())) {
            if (!var->isExistInVectors(this) && var->symbol() != _symbol) {
                var->matchVariables()->push_back(this);
            }
            if (!isExistInVectors(var) && _symbol != var->symbol()) {
                _matchVariables.push_back(var);
            }
        }
//        for (Variable *var : *(variable->matchVariables())) {
//            var->matchVariables()->assign(var->matchVariables()->begin(), var->matchVariables()->end());
//        }
    } */
    
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
    vector<Variable *> _matchVariables;
};

#endif
