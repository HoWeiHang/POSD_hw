//
//  Term.cpp
//  POSDhomework
//
//  Created by Ｗillie on 10/1/17.
//  Copyright © 2017 Ｗillie. All rights reserved.
//

#include "term.h"
#include "variable.h"
#include <typeinfo>
#include <vector>
#include "struct.h"

bool Term::match(Term &term) {
    Variable *variable = dynamic_cast<Variable *>(this);
    Variable *variableCastFromTerm = dynamic_cast<Variable *>(&term);
    Struct *structCastFromTerm = dynamic_cast<Struct *>(&term);
    if (variable && variableCastFromTerm) {
        variable->setValue(variableCastFromTerm->symbol());
        variable->addMatchVariable(variableCastFromTerm);
        variableCastFromTerm->addMatchVariable(variable);
        return variable->isUpdateValueForMatchVariablesSuccess(variableCastFromTerm->value());
    } else if (variable) {
        if (structCastFromTerm) {
            variable->setMatchStruct(structCastFromTerm);
        }
        return isVariableMatchSuccess(term, variable);
    } else if (typeid(*this) == typeid(term)) {
        return symbol() == term.symbol();
    } else if (variableCastFromTerm) {
        return isVariableMatchSuccess(*this, variableCastFromTerm);
    }
    return false;
}

bool Term::isVariableMatchSuccess(Variable *variable, Term &matchTerm) {
    if (variable->isAssignable(&matchTerm)) {
        return variable->isUpdateValueForMatchVariablesSuccess(matchTerm.symbol(), &matchTerm);
    }
    return false;
}

bool Term::isVariableMatchSuccess(Term &matchTerm, Variable *variable) {
    return variable->isUpdateValueForMatchVariablesSuccess(matchTerm.symbol());
}
