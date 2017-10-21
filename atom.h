#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
using std::string;

class Atom : public Term{
public:
    Atom(string s):Term(s) {}
};

class Number : public Term{
public:
    Number(double db):Term(db) {}
};

#endif
