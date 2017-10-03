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

bool SimpleObject::match(SimpleObject *simpleObject) {
    Variable *variable = dynamic_cast<Variable *>(this);
    Variable *variableCastFromSimpleObject = dynamic_cast<Variable *>(simpleObject);
    if (variable && variableCastFromSimpleObject) {
        return true;
    } else if (variable) {
        bool matchSuccess = false;
        if (variable->_isAssignable(simpleObject)) {
            variable->setValue(simpleObject->symbol());
            matchSuccess = true;
        }
        return matchSuccess;
    } else if (typeid(*this) == typeid(*simpleObject)) {
        return symbol() == simpleObject->symbol();
    } else if (variableCastFromSimpleObject) {
        bool matchSuccess = false;
        if (variableCastFromSimpleObject->_isAssignable(this)) {
            variableCastFromSimpleObject->setValue(symbol());
            setValue(variableCastFromSimpleObject->symbol());
            matchSuccess = true;
        }
        return matchSuccess;
    }
    return false;
}
