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
#include "node.h"

#include "utParser.h"

class Parser {
public:
    Parser(Scanner scanner) : _scanner(scanner), _terms(){}

    Term* createTerm(){
      int token = _scanner.nextToken();
      _currentToken = token;
      if(token == VAR) {
        return new Variable(symtable[_scanner.tokenValue()].first);
      } else if(token == NUMBER) {
        return new Number(_scanner.tokenValue());
      } else if(token == ATOM || token == ATOMSC) {
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '(' ) {
          return structure();
        } else {
          return atom;
        }
      } else if(token == '[') {
        return list();
      }

      return nullptr;
    }

    Term * structure() {
      Atom structName = Atom(symtable[_scanner.tokenValue()].first);
      int startIndexOfStructArgs = _terms.size();
      _scanner.nextToken();
      createTerms();
      if(_currentToken == ')')
      {
        vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
        _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
        return new Struct(structName, args);
      } else {
        throw string("unexpected token");
      }
    }

    Term * list() {
      int startIndexOfListArgs = _terms.size();
      createTerms();
      if(_currentToken == ']')
      {
        vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
        _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
        return new List(args);
      } else {
        throw string("unexpected token");
      }
    }
    
    void matchings() {
        _tree = createTree();
        preOrder(_tree);
    }
    
    void preOrder(Node *node) {
        if (node->payload == TERM) {
            _terms.push_back(node->term);
        }
        if (node->left != 0) {
            preOrder(node->left);
        }
        if (node->right != 0) {
            preOrder(node->right);
        }
    }
    
    string removeEndDot(string s) {
        return s.substr(0, s.length() - 1);
    }
    
    Node *expressionTree() {
        return _tree ? _tree : createTree();
    }
    
    Node *createTree() {
        _nodeVariables.clear();
        _scanner.clearPos();
        Node topNode(EQUALITY);
        string processedString = removeEndDot(_scanner.getBuffer());
        string leftString = split(processedString);
        string rightString;
        if (leftString != processedString) {
            topNode.payload = operatorsWithChar(_topPayload);
            topNode.left = createNode(*this, false, false);
            rightString = _scanner.getBuffer().substr(_currentPayloadPosition + 1, processedString.length() - _currentPayloadPosition);
            return new Node(topNode.payload, 0, topNode.left, recursionNode(rightString));
        } else {
            Term *term = createTerm();
            Node *leftTerm = new Node(TERM, term, 0, 0);
            Operators op = operatorsWithChar(_scanner.nextToken());
            Node *rightTerm = new Node(TERM, createTerm(), 0 ,0);
            return new Node(op, 0, leftTerm, rightTerm);
        }
        return 0;
    }
    
    Node *recursionNode(string rightStr) {
        bool isSame = operatorsWithChar(_topPayload) == COMMA;
        if (!isSame) {_nodeVariables.clear();}
        string leftString = split(rightStr);
        Scanner scanner(leftString);
        Parser parser(scanner);
        string rightString;
        if (leftString != rightStr) {
            Node node(EQUALITY);
            node.payload = operatorsWithChar(_topPayload);
            node.left = createNode(parser, true, isSame);
            rightString = rightStr.substr(_currentPayloadPosition + 1, rightStr.length() - _currentPayloadPosition);
            return new Node(node.payload, 0, node.left, recursionNode(rightString));
        } else {
            scanner.nextToken();
            return createNode(parser, true, isSame);
        }
    }
    
    Node *createNode(Parser &parser, bool isRecursion, bool isSame) {
        Node *leftTermNode = createTermNode(parser, true, isSame);
        Operators op = operatorsWithChar(parser.getScanner()->nextToken());
        Node *rightTermNode = createTermNode(parser, true, isSame);
        return new Node(op, 0, leftTermNode, rightTermNode);
    }
    
    Node *createTermNode(Parser &parser, bool isRecursion, bool isSame) {
        Term *term = parser.createTerm();
        processStruct(term);
        Node *node = new Node(TERM, isRecursion && isSame && getSameTerm(term) ? getSameTerm(term) : term, 0, 0);
        if (isVariable(node->term) && !isInNodeVariables(node->term)) {
            _nodeVariables.push_back(node->term);
        }
        return node;
    }
    
    bool isVariable(Term *term) {
        Variable *var = dynamic_cast<Variable *>(term);
        return var;
    }
    
    bool isInNodeVariables(Term *term) {
        for (Term *variable : _nodeVariables) {
            if (term == variable) {
                return true;
            }
        }
        return false;
    }
    
    void processStruct(Term *term) {
        Struct *s = dynamic_cast<Struct *>(term);
        if (s) {
            for (Term *variablePointer: *s->getVariables()) {
                if (getSameTerm(variablePointer)) {    // sync variable pointer in Struct
                    s->getVarLocatedStruct(s)->setArgs({getSameTerm(variablePointer)});
                    variablePointer = getSameTerm(variablePointer);
                } else if (!isInNodeVariables(variablePointer)) {   // if struct contains Variable, save that Variable
                    _nodeVariables.push_back(variablePointer);
                }
            }
        }
    }
    
    Term *getSameTerm(Term *term) {
        for (Term *variable : _nodeVariables) {
            if (term->symbol() == variable->symbol()) {
                return variable;
            }
        }
        return 0;
    }
    
    string split(string s) {
        int count = 0;
        bool illegal = false;
        for (char &c : s) {
            if (c == '(') {
                illegal = true;
            }
            if (c == ')') {
                illegal = false;
            }
            if (!illegal && (c == ';' || c == ',')) {
                _topPayload = c;
                break;
            }
            count++;
        }
        _currentPayloadPosition = count;
        return s.substr(0, count);
    }
    
    Scanner *getScanner() {
        return &_scanner;
    }

    vector<Term *> & getTerms() {
      return _terms;
    }

private:
    FRIEND_TEST(ParserTest, createArgs);
    FRIEND_TEST(ParserTest,ListOfTermsEmpty);
    FRIEND_TEST(ParserTest,listofTermsTwoNumber);
    FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

    void createTerms() {
      Term* term = createTerm();
      if(term!=nullptr)
      {
        _terms.push_back(term);
        while((_currentToken = _scanner.nextToken()) == ',') {
          _terms.push_back(createTerm());
        }
      }
    }

    vector<Term *> _terms;
    vector<Term *> _nodeVariables;
    Scanner _scanner;
    int _currentToken;
    int _currentPayloadPosition;
    char _topPayload;
    Node *_tree = nullptr;
};
#endif
