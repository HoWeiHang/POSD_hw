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
using std::string;

class Number {
public:
    Number(string symbol) : _symbol(symbol) {}
    string symbol() { return _symbol; }
    string value() { return std::to_string(_value); }
    void setValue(int value) { _value = value; }
private:
    string const _symbol;
    int _value;
};

#endif 
