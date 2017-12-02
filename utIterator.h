#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "iterator.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term *> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term *> *it = s.createIterator();
  it->first();
  it->next();

  Iterator<Term *> *it2 = it->currentItem()->createIterator();
  it2->first();
  ASSERT_EQ("X", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_EQ("2", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_TRUE(it2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term *> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1); 
  NullIterator<Term *> nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator<Term *> *it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

// s(t(X, 1), Y, 2)
TEST(iterator, structFirstDFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &one });
    Struct s(Atom("s"), { &t, &Y, &two });
    Iterator<Term *> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("t(X, 1)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

// s(t(X, 1, z(3)), Y, [2, v(1, 2, 3)])
TEST(iterator, structSecondDFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Number three(3);
    Struct z(Atom("z"), { &three });
    Struct t(Atom("t"), { &X, &one, &z });
    Struct v(Atom("v"), { &one, &two, &three});
    List l({ &two, &v });
    Struct s(Atom("s"), { &t, &Y, &l });
    Iterator<Term *> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("t(X, 1, z(3))", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("z(3)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[2, v(1, 2, 3)]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("v(1, 2, 3)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

// s(t(X, 1), Y, 2)
TEST(iterator, structFirstBFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &one });
    Struct s(Atom("s"), { &t, &Y, &two });
    Iterator<Term *> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("t(X, 1)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

// s(t(X, 1, z(3)), Y, [2, v(1, 2, 3)])
TEST(iterator, structSecondBFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Number three(3);
    Struct z(Atom("z"), { &three });
    Struct t(Atom("t"), { &X, &one, &z });
    Struct v(Atom("v"), { &one, &two, &three});
    List l({ &two, &v });
    Struct s(Atom("s"), { &t, &Y, &l });
    Iterator<Term *> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("t(X, 1, z(3))", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[2, v(1, 2, 3)]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("z(3)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("v(1, 2, 3)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

// [[X, 1], Y, 2]
TEST(iterator, listFirstDFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    List l({ &X, &one });
    List l2({ &l, &Y, &two });
    Iterator<Term *> *it = l2.createDFSIterator();
    it->first();
    ASSERT_EQ("[X, 1]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

// [t(X, 1, z(3)), Y, [2, v(1, 2, 3)]]
TEST(iterator, listSecondDFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Number three(3);
    Struct z(Atom("z"), { &three });
    Struct t(Atom("t"), { &X, &one, &z });
    Struct v(Atom("v"), { &one, &two, &three});
    List l({ &two, &v });
    List l2({ &t, &Y, &l});
    Iterator<Term *> *it = l2.createDFSIterator();
    it->first();
    ASSERT_EQ("t(X, 1, z(3))", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("z(3)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[2, v(1, 2, 3)]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("v(1, 2, 3)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

// [[X, 1], Y, 2]
TEST(iterator, listFirstBFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    List l({ &X, &one });
    List l2({ &l, &Y, &two });
    Iterator<Term *> *it = l2.createBFSIterator();
    it->first();
    ASSERT_EQ("[X, 1]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

// s(t(X, 1, z(3)), Y, [2, v(1, 2, 3)])
TEST(iterator, listSecondBFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Number three(3);
    Struct z(Atom("z"), { &three });
    Struct t(Atom("t"), { &X, &one, &z });
    Struct v(Atom("v"), { &one, &two, &three});
    List l({ &two, &v });
    List l2({ &t, &Y, &l});
    Iterator<Term *> *it = l2.createBFSIterator();
    it->first();
    ASSERT_EQ("t(X, 1, z(3))", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[2, v(1, 2, 3)]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("z(3)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("v(1, 2, 3)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("3", it->currentItem()->symbol());
    ASSERT_TRUE(it->isDone());
}

/*****
TEST(Iterator, DFS_OneMatching) {
  Scanner scanner("X=1.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createDFSIterator();
  it->first();

  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, DFS_TwoTermsMatching) {
  Scanner scanner("X=1, Y=2.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createDFSIterator();
  it->first();

  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, DFS_ThreeTermsMatching1) {
  Scanner scanner("X=1, Y=2, Z=3.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createDFSIterator();
  it->first();

  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Z", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, DFS_ThreeTermsMatching2) {
  Scanner scanner("X=1, Y=2; Z=3.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createDFSIterator();
  it->first();

  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ(";", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Z", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, DFS_ThreeTermsMatching3) {
  Scanner scanner("X=1; X=2, Y=s(s(X)).");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createDFSIterator();

  it->first();
  ASSERT_EQ(";", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("s(s(X))", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, BFS_OneMatching) {
  Scanner scanner("X=1.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createBFSIterator();
  it->first();

  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, BFS_TwoTermsMatching) {
  Scanner scanner("X=1, Y=2.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createBFSIterator();
  it->first();

  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, BFS_ThreeTermsMatching1) {
  Scanner scanner("X=1, Y=2, Z=3.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createBFSIterator();

  it->first();
  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Z", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, BFS_ThreeTermsMatching2) {
  Scanner scanner("X=1, Y=2; Z=3.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createBFSIterator();
  it->first();

  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ(";", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Z", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}

TEST(Iterator, BFS_ThreeTermsMatching3) {
  Scanner scanner("X=1; X=2, Y=s(s(X)).");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();

  Iterator * it = et->createBFSIterator();

  it->first();
  ASSERT_EQ(";", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ(",", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("Y", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("s(s(X))", it->currentItem()->symbol());
  ASSERT_TRUE(it->isDone());
}
*****/
#endif
