//
//  main.cpp
//  POSDHomework
//
//  Created by Ｗillie on 9/19/17.
//  Copyright © 2017 Ｗillie. All rights reserved.
//

#include <gtest/gtest.h>
#include "utAtom.h"
#include "utVariable.h"
#include "utTerm.h"
#include "utStruct.h"
#include "utList.h"
#include "utScanner.h"
#include "utParser.h"

int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv );
    return RUN_ALL_TESTS( ) ;
}
