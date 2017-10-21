#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <typeinfo>
#include "atom.h"
#include "list.h"

using std::string;

class Variable : public Term {
public:
    Variable(string s):Term(s), _inst(0){}
    
    string value() const {
        if (_inst)
            return _inst->value();
        else
            return Term::value();
    }
    
    bool match(Term &term) {
        if (this == &term)
            return true;
        List *list = dynamic_cast<List *>(&term);
        if (list && list->isContainVar(this)) {
            return false;
        }
        if(!_inst){
            _inst = &term ;
            return true;
        }
        return _inst->match(term);
    }
private:
  Term * _inst;
};

#endif
