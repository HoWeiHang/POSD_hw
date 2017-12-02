#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include "node.h"
#include <queue>

using std::queue;

class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const = 0;
};

class NullIterator :public Iterator{
public:
  NullIterator(Term *n) {}
  void first(){}
  void next(){}
  Term * currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

class StructIterator :public Iterator {
public:
  friend class Struct;

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

class ListIterator :public Iterator {
public:
  friend class List;

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  ListIterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};

class DFSIterator :public Iterator {
public:
    DFSIterator(Term *term): _term(term){}
    
    void first() {
        _index = 0;
        preOrder(_term);
    }
    
    Term* currentItem() const {
        return _term;
    }
    
    bool isDone() const {
        return _index == _terms.size() - 1;
    }
    
    void next() {
        _index++;
        _term = _terms[_index];
    }
    
    void preOrder(Term *term) {
        _terms.push_back(term);
        if (term->getArgs()) {
            for (Term *termInArgs: *term->getArgs()) {
                preOrder(termInArgs);
            }
        }
    }
    
private:
    int _index;
    Term *_term;
    std::vector<Term *> _terms;
};

class BFSIterator :public Iterator {
public:
    BFSIterator(Term *term): _term(term){}
    
    void first() {
        _index = 0;
        doBreadthFirst();
    }
    
    Term *currentItem() const {
        return _term;
    }
    
    bool isDone() const {
        return _index == _terms.size() - 1;
    }
    
    void next() {
        _index++;
        _term = _terms[_index];
    }
    
    void doBreadthFirst() {
        queue<Term *> queue;
        queue.push(_term);
        while (!queue.empty())
        {
            Term *tmpTerm = queue.front();
            queue.pop();
            _terms.push_back(tmpTerm);
            if (tmpTerm->getArgs()) {
                for (Term *term: *tmpTerm->getArgs()) {
                    queue.push(term);
                }
            }
        }
    }
    
private:
    int _index;
    Term *_term;
    std::vector<Term *> _terms;
};

/*****************************************
 * Willie Ho : for TA's tests
 *****************************************/
/*
class DFSIterator :public Iterator {
public:
    DFSIterator(Node *node): _node(node){}

    void first() {
        _index = 0;
        preOrder(_node);
    }

    Term* currentItem() const {
        return _node->term;
    }

    bool isDone() const {
        return _index == _nodes.size() - 1;
    }

    void next() {
        _index++;
        _node = _nodes[_index];
    }

    void preOrder(Node *node) {
        _nodes.push_back(node);
        if (node->left != 0) {
            preOrder(node->left);
        }
        if (node->right != 0) {
            preOrder(node->right);
        }
    }

private:
    int _index;
    Node *_node;
    std::vector<Node *> _nodes;
};

class BFSIterator :public Iterator {
public:
    BFSIterator(Node *node): _node(node){}

    void first() {
        _index = 0;
        doBreadthFirst();
    }

    Term *currentItem() const {
        return _node->term;
    }

    bool isDone() const {
        return _index == _nodes.size() - 1;
    }

    void next() {
        _index++;
        _node = _nodes[_index];
    }

    void doBreadthFirst() {
        queue<Node *> queue;
        queue.push(_node);
        while (!queue.empty())
        {
            Node *tmpNode = queue.front();
            queue.pop();
            _nodes.push_back(tmpNode);

            if (tmpNode->left != 0)
                queue.push(tmpNode->left);
            if (tmpNode->right != 0)
                queue.push(tmpNode->right);
        }
    }

private:
    int _index;
    Node *_node;
    std::vector<Node *> _nodes;
};
*/

#endif
