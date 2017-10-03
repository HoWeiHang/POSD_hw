#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "simpleObject.h"

using std::string;

class Variable : public SimpleObject {
public:
    Variable(string s, string typeName = "Variable") : SimpleObject(typeName), _symbol(s) {}
    string symbol() const { return _symbol; }
	string value() { return _value; }
    void setValue(string value) { _value = value; }
    bool _isAssignable(SimpleObject *simpleObject) {
        return _value == "" || _value == simpleObject->symbol();
    }
private:
    string const _symbol;
    string _value;
};

#endif
