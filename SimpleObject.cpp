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

bool SimpleObject::match(SimpleObject &simpleObject) {
    Variable *variable = dynamic_cast<Variable *>(this);
    Variable *variableCastFromSimpleObject = dynamic_cast<Variable *>(&simpleObject);
    if (variable && variableCastFromSimpleObject) {
        return true;
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
    bool matchSuccess = false;
    if (variable->_isAssignable(&matchSimpleObject)) {
        variable->setValue(matchSimpleObject.symbol());
        matchSuccess = true;
    }
    return matchSuccess;
}
