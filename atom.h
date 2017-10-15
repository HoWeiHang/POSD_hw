#ifndef ATOM_H
#define ATOM_H
#include <string>
#include "simpleObject.h"

using std::string;

class Atom : public SimpleObject {
public:
    Atom (string s, string typeName = "Atom") : SimpleObject(typeName), _symbol(s) {}
    string symbol() { return _symbol; }
    string value() { return _symbol; }
private:
    string const _symbol;
};

#endif
