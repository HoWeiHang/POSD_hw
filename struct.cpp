//
//  struct.cpp
//  1123POSD
//
//  Created by Willie on 2017/12/1.
//  Copyright © 2017年 Willie. All rights reserved.
//

#include "struct.h"
#include "iterator.h"

Iterator * Struct::createIterator() {
    return new StructIterator(this);
}

Iterator *Struct::createDFSIterator() {
    return new DFSIterator(this);
}

Iterator *Struct::createBFSIterator() {
    return new BFSIterator(this);
}
