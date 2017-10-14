//
//  SimpleObject.cpp
//  POSDhomework
//
//  Created by Ｗillie on 10/1/17.
//  Copyright © 2017 Ｗillie. All rights reserved.
//

#include "simpleObject.h"
#include "variable.h"
#include <typeinfo>
#include <vector>

bool SimpleObject::match(SimpleObject &simpleObject) {
    Variable *variable = dynamic_cast<Variable *>(this);
    Variable *variableCastFromSimpleObject = dynamic_cast<Variable *>(&simpleObject);
    if (variable && variableCastFromSimpleObject) {
        variable->addMatchVariable(variableCastFromSimpleObject);
        variableCastFromSimpleObject->addMatchVariable(variable);
        return variable->isUpdateValueForMatchVariablesSuccess(variableCastFromSimpleObject->value(), variableCastFromSimpleObject) && variableCastFromSimpleObject->isUpdateValueForMatchVariablesSuccess(variable->value(), variable);
    } else if (variable) {
        return isVariableMatchSuccess(variable, simpleObject);
    } else if (typeid(*this) == typeid(simpleObject)) {
        return symbol() == simpleObject.symbol();
    } else if (variableCastFromSimpleObject) {
        return isVariableMatchSuccess(variableCastFromSimpleObject, *this);
    }
    return false;
}

bool SimpleObject::isVariableMatchSuccess(Variable *variable, SimpleObject &matchSimpleObject) {
    if (variable->isAssignable(&matchSimpleObject)) {
        return variable->isUpdateValueForMatchVariablesSuccess(matchSimpleObject.symbol(), &matchSimpleObject);
//        for (Variable *var : variable->matchVariables()) {
//            if (!var->isAssignable(&matchSimpleObject)) {
//                return false;
//            }
//            var->setValue(matchSimpleObject.symbol());
//        }
//        variable->setValue(matchSimpleObject.symbol());
//        return true;
    }
    return false;
}
