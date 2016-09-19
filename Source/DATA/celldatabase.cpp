//
//  celldatabase.cpp
//  OP2A
//
//  Created by Kim M.K. on 16/09/2016.
//  Copyright © 2016 Kim M.K. All rights reserved.
//

#include "celldatabase.hpp"
#include "dataMaxDefinition.hpp"


CellDataBase::CellDataBase()
{
    Q.reserve(MAXNSPEC+3+MAXNENER);
};


CellDataBase::~CellDataBase()
{
    
};