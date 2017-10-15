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
    if (isAssignable(this) && _matchVariables.empty()) {
        return _symbol;
    }
    if (_value.empty()) {
        return _symbol;
    }
    return _value;
}

bool Variable::isUpdateValueForMatchVariablesSuccess (string value, Term *term) {
    Variable *variable = dynamic_cast<Variable *>(term);
    for (Variable *var : _matchVariables) {
        if (!var->isAssignable(term) && !variable) {
            return false;
        }
        var->setValue(value);
    }
    if (isAssignable(term) && term != this) {
        setValue(value);
    }
    return true;
}

bool Variable::isUpdateValueForMatchVariablesSuccess (string value) {
    if (!isAssignable(this, value)) {
        return false;
    }
    for (Variable *var : _matchVariables) {
        var->setValue(value);
    }
    setValue(value);
    return true;
}

