#ifndef ATOM_H
#define ATOM_H
#include <string>
#include "term.h"

using std::string;

class Atom : public Term {
public:
    Atom (string s, string typeName = "Atom") : Term(typeName), _symbol(s) {}
    string symbol() { return _symbol; }
    string value() { return _symbol; }
private:
    string const _symbol;
};

#endif
