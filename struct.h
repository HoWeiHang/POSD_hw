#ifndef STRUCT_H
#define STRUCT_H
#include "atom.h"
#include "variable.h"
#include <vector>
#include <string>
#include <map>

using std::string;
using std::map;
using std::pair;

enum StructComponent {
    StructComponentSymbol,
    StructComponentValue
};

class Struct : public Term {
public:
    Struct(Atom const &name, std::vector<Term *> args, string typeName = "Struct") : Term(typeName), _name(name), _args(args) {
        setUpVariable();
        setUpStructure();
    }
    
    string symbol() {
        return sa(StructComponentSymbol);
    }
    
    string value() {
        return sa(StructComponentValue);
    }
    
    std::vector<Variable *> variables() {
        return _variables;
    }
    
    std::vector<Struct *> structs() {
        return _structs;
    }
    
    string componentSymbol() {
        return _name.symbol() + "(" + variable()->symbol() + ")";
    }
    
    string componentValue() {
        string returnString = variable()->value().empty() ? variable()->symbol() : variable()->value();
        return _name.symbol() + "(" + returnString + ")";
    }
    
    string sa(StructComponent sc) {
        string returnString = _name.symbol() + "(";
        string structString = "";
        string variableString = "";
//        Struct *currentStruct = this;
//        std::vector<Variable *> vv;
//        std::vector<Struct *> sv;
//        while (currentStruct->structure()) {
//
//        }
        for (Struct *str : _structs) {
            if (_variables.empty() && str == _structs.back()) {
                returnString += sc == StructComponentSymbol ? str->componentSymbol() + ")" : str->componentValue() + ")";
            } else {
                returnString += sc == StructComponentSymbol ? str->componentSymbol() + ", " : str->componentValue() + ", ";
            }
        }
        for (Variable *var : _variables) {
            if (var == _variables.back()) {
                returnString += sc == StructComponentSymbol ? var->symbol() + ")" : var->value() + ")";
            } else {
                returnString += sc == StructComponentSymbol ? var->symbol() + ", " : var->value() + ", ";
            }
//            returnString += var == _variables.back() ? var->symbol() + ")" : var->symbol() + ", ";
        }
        return returnString;
    }
    
    string structureArchitecture(StructComponent structComponent) {
        string returnString = _name.symbol() + "(";
        string structString = "";
        string variableString = "";
        Struct *currentStruct = this;
        if (currentStruct->structs().empty() && !currentStruct->variables().empty()) {
            return structComponent == StructComponentSymbol ? currentStruct->componentSymbol() : currentStruct->componentValue();
        }
        while (currentStruct->structure()) {
            if (currentStruct->structure() && currentStruct->variable()) {
                if (currentStruct->structure()->structure()) {
                    variableString = ", " + varString(structComponent, currentStruct) + ")" + variableString;
                } else {
                    variableString = ", " + varString(structComponent, currentStruct)  + variableString;
                }
                structString += strString(structComponent, currentStruct);
                currentStruct = currentStruct->structure();
            } else if (currentStruct->structure()) {
                structString += strString(structComponent, currentStruct);
                currentStruct = currentStruct->structure();
            }
        }
        returnString += structString + variableString + ")";
        return returnString;
    }
    
    string varString(StructComponent structComponent, Struct *currentStruct) {
        return structComponent == StructComponentSymbol ? currentStruct->variable()->symbol() : currentStruct->variable()->value();
    }
    
    string strString(StructComponent structComponent, Struct *currentStruct) {
        return structComponent == StructComponentSymbol ? currentStruct->structure()->componentSymbol() : currentStruct->structure()->componentValue();
    }
    
    Variable *variable() {
        for (Term *term : _args) {
            Variable *var = dynamic_cast<Variable *>(term);
            if (var) {
                return var;
            }
        }
        return nullptr;
    }
    
    Struct *structure() {
        for (Term *term : _args) {
            Struct *stru = dynamic_cast<Struct *>(term);
            if (stru) {
                return stru;
            }
        }
        return nullptr;
    }
    
    void setUpVariable() {
        for (Term *term : _args) {
            Variable *var = dynamic_cast<Variable *>(term);
            if (var) {
                _variables.push_back(var);
            }
        }
    }
    
    void setUpStructure() {
        for (Term *term : _args) {
            Struct *stru = dynamic_cast<Struct *>(term);
            if (stru) {
                _structs.push_back(stru);
            }
        }
    }

    Term * args(int index) {
        return _args[index];
    }

    Atom &name() {
        return _name;
    }
    
    bool match(Term &term) {
        Struct *ps = dynamic_cast<Struct *>(&term);
        Variable *variable = dynamic_cast<Variable *>(&term);
        if (ps) {
            if (!_name.match(ps->_name) || _args.size() != ps->_args.size())
                return false;
            for(int i = 0; i < _args.size(); i++){
                if(_args[i]->symbol() != ps->_args[i]->symbol())
                    return false;
            }
            return true;
        }
        return false;
    }
private:
    Atom _name;
    std::vector<Term *> _args;
    std::vector<Variable *> _variables;
    std::vector<Struct *> _structs;
};

#endif
