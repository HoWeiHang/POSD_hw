//
//  Term.h
//  POSDhomework
//
//  Created by Ｗillie on 10/1/17.
//  Copyright © 2017 Ｗillie. All rights reserved.
//

#ifndef TERM_H
#define TERM_H
#include <string>
class Variable;

using std::string;

class Term {
public:
    Term(string typeName) : _typeName(typeName) {}
    string typeName() { return _typeName; }
    virtual string symbol() = 0;
    virtual string value() = 0;
    bool match(Term &term);
private:
    string const _typeName;
    bool isVariableMatchSuccess(Term &matchTerm, Variable *variable);
};

#endif /* Term_h */
