#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"

class Parser{
public:
    Parser(Scanner scanner) : _scanner(scanner){}
    Term* createTerm(){
      string startOfStructToken = "";
      int token = _scanner.nextToken();
      if(token == VAR) {
        return new Variable(symtable[_scanner.tokenValue()].first);
      } else if(token == NUMBER) {
        return new Number(_scanner.tokenValue());
      } else if(token == ATOM) {
          Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
          if(_scanner.nextToken() == '(') {
              vector<Term*> terms = getArgs();
              if(_scanner.nextToken() == ')')
                return new Struct(*atom, terms);
          } else {
              _scanner.back();
          }
          return atom;
      } else if(token == ATOMSC && [&](string s) -> bool {
          startOfStructToken = s;
          for(string::iterator it = s.begin(); it != s.end(); ++it ) {
              if((*it) != '.') {
                  return false;
              }
          }
          return true;
      } (symtable[_scanner.tokenValue()].first)) {  // end of else if which including lambda
          if (_scanner.nextToken() == '(') {
              vector<Term*> terms = getArgs();
              if(_scanner.nextToken() == ')')
                  return new Struct(Atom(startOfStructToken), terms);
          } else {
              _scanner.back();
          }
      } else {
          _scanner.back();
          if (_scanner.nextToken() == '[') {
              vector<Term*> terms = getArgs();
              int endToken = _scanner.nextToken();
              if(endToken == ']') {
                  return new List(terms);
              } else if (endToken == ')') {
                  throw string("unexpected token");
              }
          } else {
              _scanner.back();
          }
      }
      return nullptr;
    }

    vector<Term*> getArgs()
    {
      Term* term = createTerm();
      vector<Term*> args;
      if(term)
        args.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        args.push_back(createTerm());
      }
      _scanner.back();
      return args;
    }


private:
    Scanner _scanner;
    int _currentToken;
};
#endif
