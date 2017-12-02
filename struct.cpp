//
//  struct.cpp
//  1123POSD
//
//  Created by Willie on 2017/12/1.
//  Copyright © 2017年 Willie. All rights reserved.
//

#include "struct.h"
#include "iterator.h"

Iterator<Term *> * Struct::createIterator() {
    return new StructIterator<Term *>(this);
}

Iterator<Term *> * Struct::createDFSIterator() {
    return new DFSIterator<Term *>(this);
}

Iterator<Term *> * Struct::createBFSIterator() {
    return new BFSIterator<Term *>(this);
}
