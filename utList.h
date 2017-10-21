#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
    List l;
    ASSERT_EQ("[]", l.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
    Number num(8128);
    vector<Term *> args = {&num};
    List l(args);
    ASSERT_EQ("[8128]", l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
    Atom terence_tao("terence_tao"), alan_mathison_turing("alan_mathison_turing");
    vector<Term *> args = {&terence_tao, &alan_mathison_turing};
    List l(args);
    ASSERT_EQ("[terence_tao, alan_mathison_turing]", l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable X("X");
    Variable Y("Y");
    vector<Term *> args = {&X, &Y};
    List l(args);
    ASSERT_EQ("[X, Y]", l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    Atom tom("tom");
    vector<Term *> args = {&num, &X, &terence_tao};
    List l(args);
    ASSERT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    Number matchNum(8128);
    vector<Term *> args = {&num, &X, &terence_tao};
    List l(args);
    ASSERT_FALSE(matchNum.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    vector<Term *> vectorForStruct = {&X};
    Struct s(Atom("s"), vectorForStruct);
    vector<Term *> args = {&num, &X, &terence_tao};
    List l(args);
    ASSERT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    Variable Y("Y");
    vector<Term *> args = {&num, &X, &terence_tao};
    List l(args);
    ASSERT_TRUE(Y.match(l));
    ASSERT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    vector<Term *> args = {&num, &X, &terence_tao};
    List l(args);
    ASSERT_FALSE(X.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
    Number num(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    vector<Term *> args = {&num, &X, &terence_tao};
    List l(args);
    List listConstract(args);
    ASSERT_TRUE(l.match(l));
    ASSERT_TRUE(l.match(listConstract));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
    Number num(496);
    Variable X("X");
    Variable Y("Y");
    Atom terence_tao("terence_tao");
    vector<Term *> args = {&num, &X, &terence_tao};
    vector<Term *> argsContrast = {&num, &Y, &terence_tao};
    List l(args);
    List listConstract(argsContrast);
    ASSERT_TRUE(l.match(listConstract));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
    Number num(496);
    Variable X("X");
    Number num2(8128);
    Atom terence_tao("terence_tao");
    vector<Term *> args = {&num, &X, &terence_tao};
    vector<Term *> argsContrast = {&num, &num2, &terence_tao};
    List l(args);
    List listConstract(argsContrast);
    ASSERT_TRUE(l.match(listConstract));
    ASSERT_EQ("8128", l.getVariable()->value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
    Number num(496);
    Variable X("X");
    Variable Y("Y");
    Atom alan_mathison_turing("alan_mathison_turing");
    Atom terence_tao("terence_tao");
    vector<Term *> args = {&num, &X, &terence_tao};
    List l(args);
    ASSERT_TRUE(Y.match(l));
    X.match(alan_mathison_turing);
    ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
    ASSERT_EQ("alan_mathison_turing", l.getVariable()->value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);

    EXPECT_EQ(string("first"), l.head()->symbol());
    EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);

    EXPECT_EQ(string("second"), l.tail()->head()->value());
    EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> argsForFirstList = {&f};
    List firstList(argsForFirstList);
    vector<Term *> args = {&firstList, &s, &t};
    List l(args);
    ASSERT_EQ("[first]", l.head()->symbol());
    ASSERT_EQ("[second, third]", l.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    ASSERT_EQ("third", l.tail()->tail()->head()->symbol());
    ASSERT_EQ("[]", l.tail()->tail()->tail()->value());
}
 
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
    List l;
    try {
        l.head();
        FAIL() << "Expected std::out_of_range";
    } catch(std::out_of_range const &err) {
        ASSERT_EQ(std::string("Accessing head in an empty list"), err.what());
    }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
    List l;
    try {
        l.tail();
        FAIL() << "Expected std::out_of_range";
    } catch(std::out_of_range const &err) {
        ASSERT_EQ(std::string("Accessing tail in an empty list"), err.what());
    }
}




#endif
