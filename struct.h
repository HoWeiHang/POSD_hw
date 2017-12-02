#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>
#include "variable.h"

using std::string;
using std::vector;

class Iterator;

class Struct: public Term {
public:
    Struct(Atom name, std::vector<Term *> args): _name(name) {
      _args = args;
    }

    Term * args(int index) {
      return _args[index];
    }

    Atom & name() {
      return _name;
    }
    
    string symbol() const {
      string ret = _name.symbol() + "(";
      if (!_args.empty()) {
        std::vector<Term *>::const_iterator it = _args.begin();
        for (; it != _args.end()-1; ++it)
          ret += (*it)->symbol()+", ";
        ret  += (*it)->symbol();
      }
      ret += ")";
      return ret;
    }
    
    string value() const {
      if (_args.empty()) {
        return symbol();
      }
      string ret = _name.symbol() + "(";
      std::vector<Term *>::const_iterator it = _args.begin();
      for (; it != _args.end()-1; ++it)
        ret += (*it)->value()+", ";
      ret  += (*it)->value()+")";
      return ret;
    }
    
    bool match(Term & a){
        if (typeid(a) == typeid(Variable)) {
            return a.match(*this);
        } else if (typeid(a) == typeid(Struct)) {
            Struct *s = dynamic_cast<Struct *>(&a);
            if (isContainVar() || s->isContainVar()) {
                return matchStruct(s);
            }
        }
        return symbol() == a.symbol();
    }
    
    std::vector<Term *> *getArgs() {
        return &_args;
    }
    
    void setArgs(vector<Term *> args) {
        _args = args;
    }
    
    bool matchStruct(Struct *s) {
        if (_args.size() != s->getArgs()->size())
            return false;
        for (int i = 0; i < _args.size(); i++) {
            if (!(*(_args.at(i))).match((*(s->getArgs()->at(i)))))
                return false;
        }
        return true;
    }
    
    Struct *getVarLocatedStruct(Struct *s) {
        for (Term *term : _args) {
            Struct *stru = dynamic_cast<Struct *>(term);
            if (typeid(*term) == typeid(Variable)) {
                return this;
            }
            if (stru) {
                return stru->getVarLocatedStruct(stru);
            }
        }
        return 0;
    }
    
    vector<Term *> *getVariables() {
        for (Term *term : _args) {
            vector<Term *> *v = new vector<Term *>;
            if (typeid(*term) == typeid(Variable)) {
                v->push_back(term);
            }
            Struct *s = dynamic_cast<Struct *>(term);
            if (s) { // process recursion struct like s(s(x))
                for (Term *termFromStruct: *s->getVariables()) {
                    v->push_back(termFromStruct);
                }
            }
            return v;
        }
        return 0;
    }
    
    bool isContainVar() {
        for (Term *element : _args) {
            if (typeid(*element) == typeid(Variable)) {
                return true;
            }
        }
        return false;
    }
    
    int arity() {
        return _args.size();
    }
    Iterator * createIterator();
    Iterator *createDFSIterator();
    Iterator *createBFSIterator();
private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif
