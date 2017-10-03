#ifndef UTTERM_H
#define UTTERM_H
#include "include/number.h"
#include "include/atom.h"
#include "include/variable.h"

//test Number.value()
TEST (Number,ctor) {
    Number twentyFive(25);
    Variable x("X");
    twentyFive.match(&x);
    ASSERT_EQ("X", twentyFive.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number one(1);
    EXPECT_EQ("1", one.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number firstTwentyFive(25);
    Number secondTwentyFive(25);
    ASSERT_TRUE(firstTwentyFive.match(&secondTwentyFive));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number twentyFive(25);
    Number zero(0);
    ASSERT_FALSE(twentyFive.match(&zero));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number twentyFive(25);
    Atom tom("tom");
    ASSERT_FALSE(twentyFive.match(&tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number twentyFive(25);
    Variable x("X");
    ASSERT_TRUE(twentyFive.match(&x));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom tom("tom");
    Number twentyFive(25);
    ASSERT_FALSE(tom.match(&twentyFive));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom tom("tom");
    Variable x("X");
    tom.match(&x);
    ASSERT_EQ("X", tom.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Variable x("X");
    Atom tom("tom");
    ASSERT_TRUE(x.match(&tom));
    ASSERT_TRUE(tom.match(&x));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Variable x("X");
    Atom jerry("jerry");
    Atom tom("tom");
    x.match(&jerry);
    ASSERT_EQ("jerry", x.value());
    ASSERT_FALSE(tom.match(&x));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Variable x("X");
    Number five(5);
    x.match(&five);
    ASSERT_EQ("5", x.value());
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Variable x("X");
    Number twentyFive(25);
    Number hundred(100);
    x.match(&twentyFive);
    ASSERT_EQ("25", x.value());
    ASSERT_FALSE(x.match(&hundred));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Variable x("X");
    Atom tom("tom");
    Number twentyFive(25);
    x.match(&tom);
    ASSERT_EQ("tom", x.value());
    ASSERT_FALSE(x.match(&twentyFive));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Atom tom("tom");
    Variable x("X");
    Number twentyFive(25);
    tom.match(&x);
    ASSERT_EQ("X", tom.value());
    ASSERT_FALSE(twentyFive.match(&x));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
    Variable x("X");
    Atom tom("tom");
    ASSERT_TRUE(x.match(&tom));
    ASSERT_TRUE(x.match(&tom));
}
#endif
