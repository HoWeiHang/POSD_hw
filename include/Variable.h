#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Atom.h"
using std::string;

class Variable {
public:
    Variable(string s):_symbol(s){}
    string symbol() { return _symbol; }
	string value() { return _value; }
    bool match(Atom atom) {
        bool matchSuccess = false;
        if (_value == "" || _value == atom.symbol()) {
            _value = atom.symbol() ;
            matchSuccess = true;
        }
        return matchSuccess;
    }
private:
    string const _symbol;
    string _value;
};

#endif
