//
//  list.cpp
//  testPOSD
//
//  Created by Willie on 2017/10/21.
//  Copyright © 2017年 Willie. All rights reserved.
//

#include "list.h"
#include "term.h"
#include "variable.h"

#pragma mark - public

bool List::match(Term &term) {
    bool const isVariable = typeid(term) == typeid(Variable);
    List *list = dynamic_cast<List *>(&term);
    if (symbol() == term.symbol()) {
        return true;
    }
    if (isVariable) {
        return isContainVar(&term) ? false : term.match(*this);
    } else if (list) {
        return matchList(*list);
    }
    return false;
}

Term *List::getVariable() {
    for (Term *element : _elements) {
        if (typeid(*element) == typeid(Variable)) {
            return element;
        }
    }
    return 0;
}

bool List::isContainVar(Term *term) const {
    if (term) {
        for (Term *element : _elements) {
            if (element == term) {
                return true;
            }
        }
    } else {
        for (Term *element : _elements) {
            if (typeid(*element) == typeid(Variable)) {
                return true;
            }
        }
    }
    return false;
}

#pragma mark - private

bool List::matchList(List &list) {
    if (_elements.size() != list.elements().size())
        return false;
    for (int i = 0; i < _elements.size(); i++) {
        if (!(*(_elements.at(i))).match((*(list.elements().at(i)))))
            return false;
    }
    return true;
}
