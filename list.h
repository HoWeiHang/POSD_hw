#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
#include <typeinfo>

using std::vector;
using std::string;

class List : public Term {
public:
    string symbol() const {
        if (_elements.empty()) {
            return "[]";
        }
        
        string ret = "[";
        for (Term *term : _elements) {
            if (term != _elements.back()) {
                ret += term->symbol() + ", ";
            }
        }
        ret += _elements.back()->symbol() + "]";
        return ret;
    }
    string value() const {
        if (!isContainVar(0)) {
            return symbol();
        }
        
        string ret = "[";
        for (Term *term : _elements) {
            if (term != _elements.back()) {
                ret += term->value() + ", ";
            }
        }
        ret += _elements.back()->value() + "]";
        return ret;
    }
    
    bool match(Term &term);
    
    vector<Term *> elements() {
        return _elements;
    }
    
    Term *getVariable();
    
    bool isContainVar(Term *term) const;


    List (): _elements() {}
    List (vector<Term *> const & elements):_elements(elements){}
    Term * head() const {
        if (_elements.empty()) {
            throw std::out_of_range("Accessing head in an empty list");
        }
        return _elements.front();
    }
    List * tail() const {
        if (_elements.empty()) {
            throw std::out_of_range("Accessing tail in an empty list");
        }
        vector<Term *> copyElements;
        for (Term *term : _elements) {
            if (term != _elements.front()) {
                copyElements.push_back(term);
            }
        }
        return new List(copyElements);
    }

private:
    vector<Term *> _elements;
    bool matchList(List &list);
};

#endif
