//
//  Variable.cpp
//  POSDhomework
//
//  Created by Ｗillie on 9/30/17.
//  Copyright © 2017 Ｗillie. All rights reserved.
//

#include "include/Variable.h"
#include "include/Atom.h"
#include "include/Number.h"

bool Variable::match(SimpleObject *simpleObject) {
    Variable *variable = dynamic_cast<Variable *>(simpleObject);
    if (variable) {
        return true;
    }
    Atom *atom = dynamic_cast<Atom *>(simpleObject);
    if (atom) {
        bool matchSuccess = false;
        if (Variable::_isAssignable(atom)) {
            _value = atom->symbol();
            matchSuccess = true;
        }
        return matchSuccess;
    }
    Number *number = dynamic_cast<Number *>(simpleObject);
    if (number) {
        bool matchSuccess = false;
        if (Variable::_isAssignable(number)) {
            _value = number->symbol();
            matchSuccess = true;
        }
        return matchSuccess;
    }
    return false;
}
