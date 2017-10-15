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
        variable->addMatchVariable(variableCastFromTerm);
        variableCastFromTerm->addMatchVariable(variable);
        return variable->isUpdateValueForMatchVariablesSuccess(variableCastFromTerm->value(), variableCastFromTerm) && variableCastFromTerm->isUpdateValueForMatchVariablesSuccess(variable->value(), variable);
    } else if (variable) {
        if (structCastFromTerm) {
//            if (structCastFromSimpleObject->variable()) {
//                variable->match(*structCastFromSimpleObject->variable());
//            }
            variable->setMatchStruct(structCastFromTerm);
//            return variable->isVariableMatchSuccess(variable, simpleObject);
        }
        return isVariableMatchSuccess(variable, term);
    } else if (typeid(*this) == typeid(term)) {
        return symbol() == term.symbol();
    } else if (variableCastFromTerm) {
        return isVariableMatchSuccess(variableCastFromTerm, *this);
    }
    return false;
}

bool Term::isVariableMatchSuccess(Variable *variable, Term &matchTerm) {
    if (variable->isAssignable(&matchTerm)) {
        return variable->isUpdateValueForMatchVariablesSuccess(matchTerm.symbol(), &matchTerm);
    }
    return false;
}
