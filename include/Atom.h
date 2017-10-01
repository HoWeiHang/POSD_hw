#ifndef ATOM_H
#define ATOM_H
#include <string>
#include "SimpleObject.h"
#include "Variable.h"

using std::string;

class Atom : public SimpleObject {
public:
    Atom (string s, string typeName = "Atom") : SimpleObject(typeName), _symbol(s) {}
    string symbol() const { return _symbol; }
    string value() { return _value; }
    bool match(SimpleObject *simpleObject) {
        Atom *atom = dynamic_cast<Atom *>(simpleObject);
        if (atom) {
            return _symbol == atom->symbol();
        }
        Variable *variable = dynamic_cast<Variable *>(simpleObject);
        if (variable) {
            bool matchSuccess = false;
            if (variable->_isAssignable(this)) {
                variable->setValue(_symbol);
                _value = variable->symbol();
                matchSuccess = true;
            }
            return matchSuccess;
        }
        return false;
    }
private:
    string const _symbol;
    string _value;
};

#endif
