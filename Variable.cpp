//
//  Variable.cpp
//  POSDhomework
//
//  Created by Ｗillie on 9/30/17.
//  Copyright © 2017 Ｗillie. All rights reserved.
//

#include "variable.h"
#include "struct.h"

string Variable::value() {
    if (_matchStruct) {
        return _matchStruct->value();
    }
    return _value;
}

bool Variable::isUpdateValueForMatchVariablesSuccess (string value, SimpleObject *simpleObject) {
    Variable *variable = dynamic_cast<Variable *>(simpleObject);
    for (Variable *var : _matchVariables) {
        if (!var->isAssignable(simpleObject) && !variable) {
            return false;
        }
        var->setValue(value);
    }
    setValue(value);
    return true;
}

