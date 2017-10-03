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
#include "simpleObject.h"
#include "variable.h"

using std::string;

class Number : public SimpleObject {
public:
    Number(int symbol, string typeName = "Number") : SimpleObject(typeName), _symbol(std::to_string(symbol)) {}
    string symbol() const { return _symbol; }
    string value() { return _symbol; }
private:
    string const _symbol;
};

#endif 
