#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include "node.h"
#include <queue>

using std::queue;

template <class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template <class T>
class NullIterator :public Iterator<T> {
public:
  NullIterator(T n) {}
  void first(){}
  void next(){}
  T currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }

};

template <class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;

  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
private:
  StructIterator(T s): _index(0), _s(dynamic_cast<Struct*>(s)) {}
  int _index;
  Struct* _s;
};

template <class T>
class ListIterator :public Iterator<T> {
public:
  friend class List;

  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
private:
  ListIterator(T list): _index(0), _list(dynamic_cast<List*>(list)) {}
  int _index;
  List* _list;
};

template <class T>
class DFSIterator :public Iterator<T> {
public:
    DFSIterator(T term): _term(term){}
    
    void first() {
        _index = 1;
        preOrder(_term);
    }
    
    T currentItem() const {
        return _terms[_index];
    }
    
    bool isDone() const {
        return _index == _terms.size() - 1;
    }
    
    void next() {
        _index++;
    }
    
    void preOrder(T term) {
        _terms.push_back(term);
        if (!term->createIterator()->isDone()) {
            Struct *s = dynamic_cast<Struct *>(term);
            List *l = dynamic_cast<List *>(term);
            if (s) {
                for (T termInArgs: s->getArgs()) {
                    preOrder(termInArgs);
                }
            } else if(l) {
                for (T termInArgs: l->getArgs()) {
                    preOrder(termInArgs);
                }
            }
        }
    }
    
private:
    int _index;
    T _term;
    std::vector<T> _terms;
};

template <class T>
class BFSIterator :public Iterator<T> {
public:
    BFSIterator(T term): _term(term){}
    
    void first() {
        _index = 1;
        doBreadthFirst();
    }
    
    T currentItem() const {
        return _terms[_index];
    }
    
    bool isDone() const {
        return _index == _terms.size() - 1;
    }
    
    void next() {
        _index++;
    }
    
    void doBreadthFirst() {
        queue<T> queue;
        queue.push(_term);
        while (!queue.empty())
        {
            T tmpTerm = queue.front();
            queue.pop();
            _terms.push_back(tmpTerm);
            if (!tmpTerm->createIterator()->isDone()) {
                Struct *s = dynamic_cast<Struct *>(tmpTerm);
                List *l = dynamic_cast<List *>(tmpTerm);
                if (s) {
                    for (T term: s->getArgs()) {
                        queue.push(term);
                    }
                } else if (l) {
                    for (T term: l->getArgs()) {
                        queue.push(term);
                    }
                }
            }
        }
    }
    
private:
    int _index;
    T _term;
    std::vector<T> _terms;
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
