//
//  dataCFDupdate.cpp
//  OP2A
//
//  Created by Kim M.K. on 09/03/2017.
//  Copyright © 2017 Kim M.K. All rights reserved.
//

#include "dataCFDupdate.hpp"


dataCFDupdate_ver1::dataCFDupdate_ver1()
{
    
}

dataCFDupdate_ver1::dataCFDupdate_ver1(unsigned int NS, unsigned int ND, unsigned int NE)
: dQ(NS+ND+NE, 0.0), RHS(NS+ND+NE, 0.0)
{
    
}


dataCFDupdate_ver1::~dataCFDupdate_ver1()
{
    
}


void dataCFDupdate_ver1::assignSize(unsigned int NS, unsigned int ND, unsigned int NE)
{
    int N = NS+ND+NE;
    
    dQ.resize(N);
    RHS.resize(N);
    
}