#ifndef NODE_H
#define NODE_H

#include "term.h"
//class Iterator;

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};
static Operators operatorsWithChar(char c) {
    if (c == ';') {
        return SEMICOLON;
    } else if (c == ',') {
        return COMMA;
    } else if (c == '=') {
        return EQUALITY;
    }
    return TERM;
}

class Node {
public:
    Node(Operators op):payload(op), term(0), left(0), right(0) {}
    Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}
    Operators payload;
    Term *term;
    Node *left;
    Node *right;
    
    bool evaluate() {
        if (payload == EQUALITY) {
            return left->term->match(*(right->term));
        } else if (payload == COMMA) {
            return recursionMatch(left) && recursionMatch(right);
        } else if (payload == SEMICOLON) {
            return recursionMatch(left) && recursionMatch(right);
        }
        return true;
    };
    
    bool recursionMatch(Node *node) {
        if (node->payload == EQUALITY) {
            return node->left->term->match(*(node->right->term));
        } else if (node->payload == COMMA) {
            return recursionMatch(node->left) && recursionMatch(node->right);
        } else if (node->payload == SEMICOLON) {
            return recursionMatch(node->left) || recursionMatch(node->right);
        }
        return false;
    }
    
//    Iterator * createDFSIterator();
//    Iterator * createBFSIterator();
};

#endif
