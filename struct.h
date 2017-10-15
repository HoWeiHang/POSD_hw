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

class Struct : public SimpleObject {
public:
    Struct(Atom const &name, std::vector<SimpleObject *> args, string typeName = "Struct") : SimpleObject(typeName), _name(name), _args(args) {}
    
//    string symbol() const {
//        string ret =_name.symbol() + "(";
//        for(int i = 0; i < _args.size() - 1 ; i++){
//            ret += _args[i]-> symbol() + ", ";
//        }
//        ret += _args[_args.size()-1]-> symbol() + ")";
//        return  ret;
//    }
    string symbol() {
        return structureArchitecture(StructComponentSymbol);
    }
    
    string symbol() const {
//        return structureArchitecture(StructComponentSymbol);
        return "fuck";
    }
    
    string value() {
        return structureArchitecture(StructComponentValue);
    }
    
//    string structureArchitecture() {
//        std::vector<Struct *> structVector;
//        map<Struct *, Variable *> architectureMap;
//        string returnString = _name.symbol() = "(";
//        Struct *currentStruct = this;
//        while (!currentStruct->variable() && !currentStruct->structure()) {
//            if (currentStruct->variable()) {
//                architectureMap.insert(pair<Struct *, Variable*>(currentStruct, currentStruct->variable()));
//            }
//            if (currentStruct->structure()) {
//                structVector.push_back(currentStruct->structure());
//                currentStruct = currentStruct->structure();
//            }
//        }
//        for (Struct *structure : structVector) {
//            if (structure->structure()) {
//
//            }
//        }
//    }
    string componentSymbol() const {
        return _name.symbol() + "(" + variable()->symbol() + ")";
    }
    
    string componentValue() {
        string returnString = variable()->value().empty() ? variable()->symbol() : variable()->value();
        return _name.symbol() + "(" + returnString + ")";
    }
    
    string structureArchitecture(StructComponent structComponent) {
        string returnString = _name.symbol() + "(";
        string structString = "";
        string variableString = "";
        Struct *currentStruct = this;
        if (!currentStruct->structure() && currentStruct->variable()) {
            return structComponent == StructComponentSymbol ? currentStruct->componentSymbol() : currentStruct->componentValue();
        }
        while (currentStruct->structure()) {
            if (currentStruct->structure() && currentStruct->variable()) {
                if (currentStruct->structure()->structure()) {
                    variableString = ", " + ((structComponent == StructComponentSymbol) ? currentStruct->variable()->symbol() : currentStruct->variable()->value()) + ")" + variableString;
                } else {
                    variableString = ", " + ((structComponent == StructComponentSymbol) ? currentStruct->variable()->symbol() : currentStruct->variable()->value()) + variableString;
                }
                structString += structComponent == StructComponentSymbol ? currentStruct->structure()->componentSymbol() : currentStruct->structure()->componentValue();
                currentStruct = currentStruct->structure();
            } else if (currentStruct->structure()) {
                structString += structComponent == StructComponentSymbol ? currentStruct->structure()->componentSymbol() : currentStruct->structure()->componentValue();
                currentStruct = currentStruct->structure();
            }
        }
        returnString += structString + variableString + ")";
        return returnString;
    }
    
    Variable *variable() const {
        for (SimpleObject *simpleObject : _args) {
            Variable *var = dynamic_cast<Variable *>(simpleObject);
            if (var) {
                return var;
            }
        }
        return nullptr;
    }
    
    Struct *structure() {
        for (SimpleObject *simpleObject : _args) {
            Struct *stru = dynamic_cast<Struct *>(simpleObject);
            if (stru) {
                return stru;
            }
        }
        return nullptr;
    }

    SimpleObject * args(int index) {
        return _args[index];
    }

    Atom const &name() {
        return _name;
    }
    
    bool match(SimpleObject &simpleObject) {
        Struct *ps = dynamic_cast<Struct *>(&simpleObject);
        Variable *variable = dynamic_cast<Variable *>(&simpleObject);
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
    std::vector<SimpleObject *> _args;
};

#endif
