#include "term.h"
#include "variable.h"
#include <typeinfo>
#include "iterator.h"

Iterator<Term *> * Term::createIterator(){
    return new NullIterator<Term *>(this);
}

bool Term::match(Term & a){
    if (typeid(a) == typeid(Variable))
        return a.match(*this);
    else
        return symbol() == a.symbol();
}
