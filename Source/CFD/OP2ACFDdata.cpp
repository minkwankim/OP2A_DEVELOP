//
//  OP2ACFDdata.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/02/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "OP2ACFDdata.hpp"


// 1. Base Data Function
OP2ACFD_DataBase::OP2ACFD_DataBase()
{
    
}

OP2ACFD_DataBase::OP2ACFD_DataBase(int s)
: U(s, 0.0), Q(s, 0.0)
{
    
}

OP2ACFD_DataBase::~OP2ACFD_DataBase()
{
    
}