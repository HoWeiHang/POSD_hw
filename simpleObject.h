//
//  SimpleObject.h
//  POSDhomework
//
//  Created by Ｗillie on 10/1/17.
//  Copyright © 2017 Ｗillie. All rights reserved.
//

#ifndef SimpleObject_h
#define SimpleObject_h
#include <string>

using std::string;

class SimpleObject {
public:
    SimpleObject(string typeName) : _typeName(typeName) {}
    string typeName() { return _typeName; }
    virtual string symbol() const = 0;
    virtual string value() = 0;
    bool match(SimpleObject &simpleObject);
private:
    string const _typeName;
};

#endif /* SimpleObject_h */
