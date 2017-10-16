//
//  Number.h
//  POSDhomework
//
//  Created by Ｗillie on 10/1/17.
//  Copyright © 2017 Ｗillie. All rights reserved.
//

#ifndef Number_h
#define Number_h
#include <string>
#include "term.h"

using std::string;

static std::string doubleToString(double d) {
    string s = std::to_string(d);                                //output to std::string
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);     //remove trailing 000s    (123.1200 => 123.12,  123.000 => 123.)
    return (s[s.size()-1] == '.') ? s.substr(0, s.size()-1) : s; //remove dangling decimal (123. => 123)
}

class Number : public Term {
public:
    Number(double value, string typeName = "Number") : Term(typeName), _symbol(doubleToString(value)) {}
    string symbol() { return _symbol; }
    string value() { return _symbol; }
private:
    string const _symbol;
};

#endif 
