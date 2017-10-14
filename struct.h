#ifndef STRUCT_H
#define STRUCT_H
#include "atom.h"
#include "variable.h"
#include <vector>
#include <string>

using std::string;

class Struct : public SimpleObject {
public:
    Struct(Atom const &name, std::vector<SimpleObject *> args, string typeName = "Struct") : SimpleObject(typeName), _name(name), _args(args) {}
    
    string symbol() const {
        string ret =_name.symbol() + "(";
        for(int i = 0; i < _args.size() - 1 ; i++){
            ret += _args[i]-> symbol() + ", ";
        }
        ret += _args[_args.size()-1]-> symbol() + ")";
        return  ret;
    }
    
    string value() {
        return symbol();
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
