#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "number.h"
#include "struct.h"

TEST(Variable, constructor){
    Variable X("X");
    ASSERT_EQ("X", X.symbol());
}

TEST(Variable , matching){
    Atom tom("tom");
    Variable X("X");
    X.match(tom);
    ASSERT_EQ("tom", X.value());
}

TEST (Variable , haveValue){
    Atom tom ("tom");
    Atom jerry ("jerry");
    Variable X("X");
    ASSERT_TRUE(X.match(tom));
    ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
    Variable X("X");
    Number two(2.7182);
    X.match(two);
    ASSERT_EQ("2.7182", X.value());
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
    Variable X("X");
    Variable Y("Y");
    Number one(1);
    X.match(Y);
    X.match(one);
    ASSERT_EQ("1", Y.value());
}

// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
    Variable X("X");
    Variable Y("Y");
    Number one(1);
    X.match(Y);
    Y.match(one);
    ASSERT_EQ("1", X.value());
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
    Variable X("X");
    Number one(1);
    X.match(X);
    X.match(one);
    ASSERT_EQ("1", X.value());
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
    Variable X("X");
    Variable Y("Y");
    Number one(1);
    ASSERT_TRUE(Y.match(one));
    ASSERT_EQ("1", Y.value());
    ASSERT_TRUE(X.match(Y));
    ASSERT_EQ("1", X.value());
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Number one(1);
    X.match(Y);
    Y.match(Z);
    Z.match(one);
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
    ASSERT_EQ("1", Z.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Number one(1);
    X.match(Y);
    X.match(Z);
    Z.match(one);
    ASSERT_EQ("1", X.value());
    ASSERT_EQ("1", Y.value());
    ASSERT_EQ("1", Z.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
    Variable X("X");
    Variable Y("Y");
    std::vector<Term *> v = {&X};
    Struct s(Atom("s"), v);
    Y.match(s);
    ASSERT_EQ("Y", Y.symbol());
    ASSERT_EQ("s(X)", Y.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
    Variable X("X");
    Variable Y("Y");
    std::vector<Term *> v = {&X};
    Struct s(Atom("s"), v);
    Y.match(s);
    Atom teddy("teddy");
    X.match(teddy);
    ASSERT_EQ("Y", Y.symbol());
    ASSERT_EQ("s(teddy)", Y.value());
}

//*********************************************************
TEST (Variable, test) {
    Variable X("X");
    Variable Y("Y");
    Number one(1);
    X.match(Y);
    ASSERT_EQ("Y", X.value());
    X.match(one);
    ASSERT_EQ("1", Y.value());
}
//*********************************************************

#endif
