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
        setUpTerm();
    }
    
    Atom &name() {
        return _name;
    }
    
    string symbol() {
        return structureArchitecture(StructComponentSymbol);
    }
    
    string value() {
        return structureArchitecture(StructComponentValue);
    }
    
    std::vector<Variable *> variables() {
        return _variables;
    }
    
    std::vector<Struct *> structs() {
        return _structs;
    }
    
    std::vector<Term *> termWithoutStructsAndVariables() {
        return _termsWithoutStrucsAndVariables;
    }
    
    Term * args(int index) {
        return _args[index];
    }
    
    bool match(Term &term) {
        Struct *ps = dynamic_cast<Struct *>(&term);
        if (ps) {
            if (!_name.match(ps->_name) || _args.size() != ps->_args.size())
                return false;
            for(int i = 0; i < _args.size(); i++){
                if (_args[i]->symbol() != ps->_args[i]->symbol())
                    return false;
            }
            return true;
        }
        return false;
    }
    
    string structureArchitecture(StructComponent structComponent) {
        string returnString = _name.symbol() + "(";
        for (Term *term : _termsWithoutStrucsAndVariables) {
            if (_structs.empty() && _variables.empty()) {
                returnString += term == _termsWithoutStrucsAndVariables.back() ? term->symbol() + ")" : term->symbol() + ", ";
            } else {
                returnString += term->symbol() + ", ";
            }
        }
        for (Struct *str : _structs) {
            if (_variables.empty() && str == _structs.back()) {
                returnString += structComponent == StructComponentSymbol ? str->componentSymbol() + ")" : str->componentValue() + ")";
            } else {
                returnString += structComponent == StructComponentSymbol ? str->componentSymbol() + ", " : str->componentValue() + ", ";
            }
        }
        for (Variable *var : _variables) {
            if (var == _variables.back()) {
                returnString += structComponent == StructComponentSymbol ? var->symbol() + ")" : var->value() + ")";
            } else {
                returnString += structComponent == StructComponentSymbol ? var->symbol() + ", " : var->value() + ", ";
            }
        }
        return returnString;
    }
    
    string componentSymbol() {
        return _name.symbol() + "(" + variable()->symbol() + ")";
    }
    
    string componentValue() {
        string returnString = variable()->value().empty() ? variable()->symbol() : variable()->value();
        return _name.symbol() + "(" + returnString + ")";
    }
    
//    string structureArchitecture(StructComponent structComponent) {
//        string returnString = _name.symbol() + "(";
//        string structString = "";
//        string variableString = "";
//        Struct *currentStruct = this;
//        if (currentStruct->structs().empty() && !currentStruct->variables().empty()) {
//            return structComponent == StructComponentSymbol ? currentStruct->componentSymbol() : currentStruct->componentValue();
//        }
//        while (currentStruct->structure()) {
//            if (currentStruct->structure() && currentStruct->variable()) {
//                if (currentStruct->structure()->structure()) {
//                    variableString = ", " + varString(structComponent, currentStruct) + ")" + variableString;
//                } else {
//                    variableString = ", " + varString(structComponent, currentStruct)  + variableString;
//                }
//                structString += strString(structComponent, currentStruct);
//                currentStruct = currentStruct->structure();
//            } else if (currentStruct->structure()) {
//                structString += strString(structComponent, currentStruct);
//                currentStruct = currentStruct->structure();
//            }
//        }
//        returnString += structString + variableString + ")";
//        return returnString;
//    }
    
//    string varString(StructComponent structComponent, Struct *currentStruct) {
//        return structComponent == StructComponentSymbol ? currentStruct->variable()->symbol() : currentStruct->variable()->value();
//    }
//
//    string strString(StructComponent structComponent, Struct *currentStruct) {
//        return structComponent == StructComponentSymbol ? currentStruct->structure()->componentSymbol() : currentStruct->structure()->componentValue();
//    }
    
    Variable *variable() {
        if (!variables().empty()) {
            return variables().front();
        }
        return nullptr;
    }
    
    Struct *structure() {
        if (!structs().empty()) {
            return structs().front();
        }
        return nullptr;
    }
private:
    Atom _name;
    std::vector<Term *> _args;
    std::vector<Variable *> _variables;
    std::vector<Struct *> _structs;
    std::vector<Term *> _termsWithoutStrucsAndVariables;
    
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
    
    void setUpTerm() {
        for (Term *term : _args) {
            Variable *var = dynamic_cast<Variable *>(term);
            Struct *stru = dynamic_cast<Struct *>(term);
            if (!stru && !var) {
                _termsWithoutStrucsAndVariables.push_back(term);
            }
        }
    }
};

#endif
